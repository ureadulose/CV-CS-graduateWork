#ifndef POINT_TRACKER_H
#define POINT_TRACKER_H

// OpenCV headers
//#include "opencv2/opencv.hpp"
#include <opencv2/optflow.hpp>
#include <opencv2/tracking.hpp>

class PointTracker
{
public:
	PointTracker();
	~PointTracker();

	/*! 
	* @brief method_num: 0 - Farneback, 1 - HornSchunck
	*/
	cv::Point2f Track(cv::Mat& frame1, cv::Mat& frame2, cv::Point2f& coords1, int method_num);

	void DrawPointOnAFrame(cv::Mat& frame, cv::Point2f& point);

};

#endif // !POINT_TRACKER_H
