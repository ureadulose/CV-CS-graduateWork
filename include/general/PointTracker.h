#ifndef POINT_TRACKER_H
#define POINT_TRACKER_H

// OpenCV headers
#include "opencv2/opencv.hpp"
#include "opencv2/optflow.hpp"

class PointTracker
{
public:
	PointTracker();
	~PointTracker();

	cv::Point2f Track(cv::Mat& frame1, cv::Mat& frame2, cv::Point2f& coords1);

	void DrawPointOnAFrame(cv::Mat& frame, cv::Point2f& point);

};

#endif // !POINT_TRACKER_H
