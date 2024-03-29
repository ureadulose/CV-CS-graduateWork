#include "PointsHandling/PointTracker.h"
#include <iostream>

PointTracker::PointTracker(std::vector<DataPoint *> *pts_to_be_tracked) :
    _pts2BeTracked{ pts_to_be_tracked }
{
}

PointTracker::~PointTracker()
{
}

void PointTracker::Track(cv::Mat& frame1, cv::Mat& frame2, OptflowType type)
{
	cv::Mat flow, frame1_gray, frame2_gray;

    // Transforming current and previous frames to gray scale if they arent already
	if (frame1.channels() > 1)
		cv::cvtColor(frame1, frame1_gray, cv::COLOR_BGR2GRAY);
	if (frame2.channels() > 1)
        cv::cvtColor(frame2, frame2_gray, cv::COLOR_BGR2GRAY);

    // blur frames a little bit to remove some noise
    cv::GaussianBlur(frame1_gray, frame1_gray, cv::Size(3, 3), 0);
    cv::GaussianBlur(frame2_gray, frame2_gray, cv::Size(3, 3), 0);

    switch(type)
    {
    case OptflowType::DenseFarneback:
    {
        cv::calcOpticalFlowFarneback(frame1_gray, frame2_gray, _flowFrame, 0.5, 3, 15, 3, 5, 1.2, 0);
        break;
    }
    case OptflowType::SparceToDense:
    {
        cv::optflow::calcOpticalFlowSparseToDense(frame1_gray, frame2_gray, _flowFrame, 8, 128, 0.01);
        break;
    }
    case OptflowType::SparseLucasKanade:
    {
        std::vector<cv::Point2f> prevPts;
        std::vector<cv::Point2f> nextPts;
        std::vector<uchar> status;
        std::vector<float> error;
        cv::Size winSize(60, 60);
        int maxLevel = 2;

        for (auto &point : *_pts2BeTracked)
        {
            prevPts.push_back(point->GetLastPos());
        }
        cv::calcOpticalFlowPyrLK(frame1_gray, frame2_gray, prevPts, nextPts, status, error, winSize, maxLevel,
                                 cv::TermCriteria(
                                     cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
                                     500,
                                     0.001
                                     ),
                                 cv::OPTFLOW_LK_GET_MIN_EIGENVALS);
        for (size_t i = 0; i < _pts2BeTracked->size(); i++)
        {
            (*_pts2BeTracked)[i]->AddNewPosition(nextPts[i]);
        }
        break;
    }
    case OptflowType::DeepFlow:
    {
        cv::Ptr<cv::DenseOpticalFlow> deepFlow = cv::optflow::createOptFlow_DeepFlow();
        deepFlow->calc(frame1_gray, frame2_gray, _flowFrame);

        break;
    }
    case OptflowType::SimpleFlow:
    {
        cv::Ptr<cv::DenseOpticalFlow> deepFlow = cv::optflow::createOptFlow_SimpleFlow();
        deepFlow->calc(frame1_gray, frame2_gray, _flowFrame);

        break;
    }
    case OptflowType::Calculated:
    {
        // TODO: recreate it in a more clear way. now it's just hard coding
        std::vector<cv::Mat> frame2Channels;
        cv::split(frame2, frame2Channels);
        std::vector<cv::Mat> optflowChannels(2);
        optflowChannels[0] = frame2Channels[0];
        optflowChannels[1] = frame2Channels[1];
        cv::merge(optflowChannels, _flowFrame);

        break;
    }
    }

    // after calculating flow put displacement to our points
    if ((!_flowFrame.empty()) && (_pts2BeTracked != nullptr))
    {
        for (auto &point : *_pts2BeTracked)
        {
            cv::Point2f displacement = _flowFrame.at<cv::Point2f>(point->GetLastPos().y, point->GetLastPos().x);
            point->AddNewPosition(point->GetLastPos() + displacement);
        }
    }
}

cv::Mat* PointTracker::GetOptflow()
{
    return &_flowFrame;
}
