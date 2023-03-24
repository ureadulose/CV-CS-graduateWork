#ifndef CV_FRAME_BUFFER_HANDLER_H
#define CV_FRAME_BUFFER_HANDLER_H

#include <iostream>

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

/*!
* @brief Class is meant to read video file and get two cv::Mat frames (current and previous) for further CV processing
*/
class CvFrameBufferHandler
{
public:
    CvFrameBufferHandler(const std::string& filename);
    ~CvFrameBufferHandler();

    bool Exists();

	bool ReadFrame();
    cv::Mat* GetCurrRgbFrame();
	cv::Mat* GetPrevRgbFrame();
    int GetFramerate();

private:
	cv::VideoCapture* _cap;
	cv::Mat _curr_rgb_frame;
	cv::Mat _prev_rgb_frame;
};

#endif // CV_FRAME_BUFFER_HANDLER_H
