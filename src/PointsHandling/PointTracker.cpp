#include "PointsHandling/PointTracker.h"
#include "opencv2/highgui.hpp"
#include <iostream>

PointTracker::PointTracker(std::vector<DataPoint>& pts_to_be_tracked) :
    _pts_to_be_tracked{ pts_to_be_tracked }
{
}

PointTracker::~PointTracker()
{
}

void PointTracker::Track(cv::Mat& frame1, cv::Mat& frame2, int method_num)
{
	cv::Mat flow, frame1_gray, frame2_gray;

    // Transforming current and previous frames to gray scale if they arent already
	if (frame1.channels() > 1)
		cv::cvtColor(frame1, frame1_gray, cv::COLOR_BGR2GRAY);
	if (frame2.channels() > 1)
		cv::cvtColor(frame2, frame2_gray, cv::COLOR_BGR2GRAY);

    // Calculating Optical Flow on the whole image and then calculating points displacement
    if (method_num == 1)
        int num;
        // TODO: currently this doesnt works :(
        //cv::calcOpticalFlowFarneback(frame1_gray, frame2_gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    else if (method_num == 0)
        cv::optflow::calcOpticalFlowSparseToDense(frame1_gray, frame2_gray, _flow_frame, 8, 128, 0.01);

    //int channelAmount = _flow_frame.channels();

    for (auto& point : _pts_to_be_tracked)
    {
        cv::Point2f displacement = _flow_frame.at<cv::Point2f>(point.GetLastPos().y, point.GetLastPos().x);
        point.AddPos(point.GetLastPos() + displacement);
    }

    // for Optical flow visualization
//    //extraxt x and y channels
//    cv::Mat xy[2]; //X,Y
//    cv::split(_flow_frame, xy);

//    //calculate angle and magnitude
//    cv::Mat magnitude, angle;
//    cv::cartToPolar(xy[0], xy[1], magnitude, angle, true);

//    //translate magnitude to range [0;1]
//    double mag_max;
//    cv::minMaxLoc(magnitude, 0, &mag_max);
//    magnitude.convertTo(magnitude, -1, 1.0 / mag_max);

//    //build hsv image
//    cv::Mat _hsv[3], hsv;
//    _hsv[0] = angle;
//    _hsv[1] = cv::Mat::ones(angle.size(), CV_32F);
//    _hsv[2] = magnitude;
//    cv::merge(_hsv, 3, hsv);

//    //convert to BGR and show
//    cv::Mat bgr;//CV_32FC3 matrix
//    cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);
//    cv::imshow("optical flow", bgr);

//    cv::waitKey(30);
}

cv::Mat* PointTracker::GetOptflow()
{
    return &_flow_frame;
}
