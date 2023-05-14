#include "PointsHandling/PointTracker.h"
#include "opencv2/highgui.hpp"
#include <iostream>

PointTracker::PointTracker(std::vector<QPointer<DataPoint>>& pts_to_be_tracked) :
    _pts_to_be_tracked{ pts_to_be_tracked }
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
        cv::calcOpticalFlowFarneback(frame1_gray, frame2_gray, _flow_frame, 0.5, 3, 15, 3, 5, 1.2, 0);

        for (auto &point : _pts_to_be_tracked)
        {
            cv::Point2f displacement = _flow_frame.at<cv::Point2f>(point->GetLastPos().y, point->GetLastPos().x);
            point->AddNewPosition(point->GetLastPos() + displacement);
        }
        break;
    }
    case OptflowType::SparceToDense:
    {
        // Calculating Optical Flow on the whole image and then calculating points displacement
        cv::optflow::calcOpticalFlowSparseToDense(frame1_gray, frame2_gray, _flow_frame, 8, 128, 0.01);
        for (auto &point : _pts_to_be_tracked)
        {
            cv::Point2f displacement = _flow_frame.at<cv::Point2f>(point->GetLastPos().y, point->GetLastPos().x);
            point->AddNewPosition(point->GetLastPos() + displacement);
        }
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

        for (auto &point : _pts_to_be_tracked)
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
        for (size_t i = 0; i < _pts_to_be_tracked.size(); i++)
        {
            _pts_to_be_tracked[i]->AddNewPosition(nextPts[i]);
            qDebug() << i << "-th point's displacement is " << nextPts[i].x - prevPts[i].x << "; " << nextPts[i].y - prevPts[i].y;
        }
        break;
    }
    case OptflowType::DeepFlow:
    {
        cv::Ptr<cv::DenseOpticalFlow> deepFlow = cv::optflow::createOptFlow_DeepFlow();
        deepFlow->calc(frame1_gray, frame2_gray, _flow_frame);
        for (auto &point : _pts_to_be_tracked)
        {
            cv::Point2f displacement = _flow_frame.at<cv::Point2f>(point->GetLastPos().y, point->GetLastPos().x);
            point->AddNewPosition(point->GetLastPos() + displacement);
        }
        break;
    }
    case OptflowType::SimpleFlow:
    {
        cv::Ptr<cv::DenseOpticalFlow> deepFlow = cv::optflow::createOptFlow_SimpleFlow();
        deepFlow->calc(frame1_gray, frame2_gray, _flow_frame);
        for (auto &point : _pts_to_be_tracked)
        {
            cv::Point2f displacement = _flow_frame.at<cv::Point2f>(point->GetLastPos().y, point->GetLastPos().x);
            point->AddNewPosition(point->GetLastPos() + displacement);
        }
        break;
        break;
    }
    }
}

cv::Mat* PointTracker::GetOptflow()
{
    return &_flow_frame;
}
