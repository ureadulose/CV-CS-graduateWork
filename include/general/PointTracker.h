#ifndef POINT_TRACKER_H
#define POINT_TRACKER_H

// OpenCV headers
#include "opencv2/opencv.hpp"

class PointTracker
{
public:
	PointTracker();
	~PointTracker();

	cv::Point2f Track(cv::Mat& frame1, cv::Mat& frame2, cv::Point2f& coords1);

	void DrawPointOnAFrame(cv::Mat& frame, cv::Point2f& point);

private:
	// TMP!!!!!!!!
	std::vector<cv::Point2f> _prev_coords;
	std::vector<cv::Point2f> _curr_coords;
};

#endif // !POINT_TRACKER_H
