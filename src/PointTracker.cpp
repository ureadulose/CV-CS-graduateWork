#include "general/PointTracker.h"
#include <iostream>

PointTracker::PointTracker()
{
}

PointTracker::~PointTracker()
{
}

cv::Point2f PointTracker::Track(cv::Mat& frame1, cv::Mat& frame2, cv::Point2f& input_coords, int method_num)
{
	cv::Mat flow, frame1_gray, frame2_gray;

    // Transforming current and previous frames to gray scale if they arent already
	if (frame1.channels() > 1)
		cv::cvtColor(frame1, frame1_gray, cv::COLOR_BGR2GRAY);
	if (frame2.channels() > 1)
		cv::cvtColor(frame2, frame2_gray, cv::COLOR_BGR2GRAY);

    if (method_num == 1)
        int num;
        //cv::calcOpticalFlowFarneback(frame1_gray, frame2_gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    else if (method_num == 0)
        cv::optflow::calcOpticalFlowSparseToDense(frame1_gray, frame2_gray, flow, 8, 128, 0.01);

	cv::Point2f displacement = flow.at<cv::Point2f>(input_coords.y, input_coords.x);

	input_coords += displacement;

	return cv::Point2f(input_coords.x + displacement.x, input_coords.y + displacement.y);
}

void PointTracker::DrawPointOnAFrame(cv::Mat& frame, cv::Point2f& point)
{
	cv::circle(frame, point, 10, cv::Scalar(255, 255, 255), 1, cv::FILLED);
}
