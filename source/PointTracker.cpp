#include "general/PointTracker.h"

PointTracker::PointTracker()
{
}

PointTracker::~PointTracker()
{
}

cv::Point2f PointTracker::Track(cv::Mat& frame1, cv::Mat& frame2, cv::Point2f& input_coords)
{
	_prev_coords.push_back(input_coords);

	std::vector<uchar> status;
	status.resize(_prev_coords.size());
	std::vector<float> errors;
	errors.resize(_curr_coords.size());
	cv::Size winSize(21, 21);

	cv::Mat flow, frame1_gray, frame2_gray;

	// Преобразуем текущий и предыдущий кадры в оттенки серого
	if (frame1.channels() > 1)
		cv::cvtColor(frame1, frame1_gray, cv::COLOR_BGR2GRAY);
	if (frame2.channels() > 1)
		cv::cvtColor(frame2, frame2_gray, cv::COLOR_BGR2GRAY);

	// Определим плотный оптический поток методом Farneback
	//cv::calcOpticalFlowFarneback(frame1_gray, frame2_gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

	cv::calcOpticalFlowPyrLK(frame1_gray, frame2_gray, _prev_coords, _curr_coords, status, errors, winSize);
	_prev_coords.push_back(_curr_coords.back());

	cv::Point2f displacement;// = //flow.at<cv::Point2f>(_prev_coords.back().y, _prev_coords.back().x);

	return cv::Point2f();//(/*input_coords.x + */displacement.x, /*input_coords.y + */displacement.y);
}

void PointTracker::DrawPointOnAFrame(cv::Mat& frame, cv::Point2f& point)
{
	cv::circle(frame, point, 10, cv::Scalar(255, 255, 255), 1, cv::FILLED);
}
