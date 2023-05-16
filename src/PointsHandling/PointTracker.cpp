#include "PointsHandling/PointTracker.h"
#include <iostream>

PointTracker::PointTracker(std::vector<DataPoint *> *pts_to_be_tracked) :
    _pts_to_be_tracked{ pts_to_be_tracked }
{
}

PointTracker::~PointTracker()
{
}

void PointTracker::Track(cv::Mat& frame1, cv::Mat& frame2, OptflowType type)
{
	cv::Mat flow, frame1_gray, frame2_gray;

    std::cout << "perform grayscaling" << std::endl;
    // Transforming current and previous frames to gray scale if they arent already
	if (frame1.channels() > 1)
		cv::cvtColor(frame1, frame1_gray, cv::COLOR_BGR2GRAY);
	if (frame2.channels() > 1)
        cv::cvtColor(frame2, frame2_gray, cv::COLOR_BGR2GRAY);
    std::cout << "done performing grayscaling" << std::endl;

    // blur frames a little bit to remove some noise
    cv::GaussianBlur(frame1_gray, frame1_gray, cv::Size(3, 3), 0);
    cv::GaussianBlur(frame2_gray, frame2_gray, cv::Size(3, 3), 0);

    switch(type)
    {
    case OptflowType::DenseFarneback:
    {
        cv::calcOpticalFlowFarneback(frame1_gray, frame2_gray, _flow_frame, 0.5, 3, 15, 3, 5, 1.2, 0);
        break;
    }
    case OptflowType::SparceToDense:
    {
        cv::optflow::calcOpticalFlowSparseToDense(frame1_gray, frame2_gray, _flow_frame, 8, 128, 0.01);
        break;
    }
    case OptflowType::SparseLucasKanade:
    {
        std::vector<cv::Point2f> prevPts;
        std::vector<cv::Point2f> nextPts;
        std::vector<uchar> status;
        std::vector<float> error;
        cv::Size winSize(40, 40);
        int maxLevel = 2;

        for (auto &point : *_pts_to_be_tracked)
        {
            prevPts.push_back(point->GetLastPos());
        }
        std::cout << "Started calculating opticalflowPyrLK" << std::endl;
        cv::calcOpticalFlowPyrLK(frame1_gray, frame2_gray, prevPts, nextPts, status, error, winSize, maxLevel,
                                 cv::TermCriteria(
                                     cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
                                     500,
                                     0.001
                                     ),
                                 cv::OPTFLOW_LK_GET_MIN_EIGENVALS);
        std::cout << "Stopped calculating opticalflowPyrLK" << std::endl;
        for (size_t i = 0; i < _pts_to_be_tracked->size(); i++)
        {
            (*_pts_to_be_tracked)[i]->AddNewPosition(nextPts[i]);
        }
        std::cout << "Added new point" << std::endl;
        break;
    }
    case OptflowType::DeepFlow:
    {
        cv::Ptr<cv::DenseOpticalFlow> deepFlow = cv::optflow::createOptFlow_DeepFlow();
        deepFlow->calc(frame1_gray, frame2_gray, _flow_frame);

        break;
    }
    case OptflowType::SimpleFlow:
    {
        cv::Ptr<cv::DenseOpticalFlow> deepFlow = cv::optflow::createOptFlow_SimpleFlow();
        deepFlow->calc(frame1_gray, frame2_gray, _flow_frame);

        break;
    }
    case OptflowType::Calculated:
    {
        std::cout << "Calcualted optflow" << std::endl;
        // TODO: recreate it in a more clear way. now it's just hard coding
        std::vector<cv::Mat> frame2Channels;
        cv::split(frame2, frame2Channels);
        std::vector<cv::Mat> optflowChannels(2);
        optflowChannels[0] = frame2Channels[0];
        optflowChannels[1] = frame2Channels[1];
        cv::merge(optflowChannels, _flow_frame);

        break;
    }
    }

    // after calculating flow put displacement to our points
    if ((!_flow_frame.empty()) && (_pts_to_be_tracked != nullptr))
    {
        for (auto &point : *_pts_to_be_tracked)
        {
            cv::Point2f displacement = _flow_frame.at<cv::Point2f>(point->GetLastPos().y, point->GetLastPos().x);
            point->AddNewPosition(point->GetLastPos() + displacement);
        }
    }
}

cv::Mat* PointTracker::GetOptflow()
{
    return &_flow_frame;
}
