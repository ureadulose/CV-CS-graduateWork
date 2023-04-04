#ifndef POINT_TRACKER_H
#define POINT_TRACKER_H

// OpenCV headers
#include <opencv2/optflow.hpp>
#include <opencv2/tracking.hpp>

#include "PointsHandling/DataPoint.h"

class PointTracker
{
public:
    PointTracker(std::vector<DataPoint>& pts_to_be_tracked);
	~PointTracker();

	/*! 
	* @brief method_num: 0 - Farneback, 1 - HornSchunck
	*/
    void Track(cv::Mat& frame1, cv::Mat& frame2, int method_num);

private:
    std::vector<DataPoint>& _pts_to_be_tracked;

};

#endif // !POINT_TRACKER_H