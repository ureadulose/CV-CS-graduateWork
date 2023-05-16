#ifndef CV_FRAME_BUFFER_HANDLER_H
#define CV_FRAME_BUFFER_HANDLER_H

#include <iostream>
#include <filesystem>

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
    CvFrameBufferHandler(const std::string& filename, bool outputVideo = true);
    ~CvFrameBufferHandler();

    bool Exists();

	bool ReadFrame();
    bool WriteFrame(cv::Mat &frame);
    cv::Mat* GetCurrRgbFrame();
	cv::Mat* GetPrevRgbFrame();
    int GetFramerate();
    cv::Size GetFrameSize();
    int GetChannelsAmount();

private:
    void initializeVideoWriter(const std::string& filename);

private:
    cv::VideoCapture* _videoCap;
    cv::VideoWriter* _writerCap;
	cv::Mat _curr_rgb_frame;
	cv::Mat _prev_rgb_frame;
};

#endif // CV_FRAME_BUFFER_HANDLER_H
