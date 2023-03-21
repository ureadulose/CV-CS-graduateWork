#ifndef VIDEO_HANDLER_H
#define VIDEO_HANDLER_H

#include <iostream>
#include "opencv2/highgui.hpp"

/*!
* @brief Класс предназначен для чтения видео-файла и получения cv::Mat изображения
*/
class VideoHandler
{
public:
	VideoHandler(const std::string& filename);
	~VideoHandler();

	bool ReadFrame();
	cv::Mat* GetCurrRgbFrame();
	cv::Mat* GetPrevRgbFrame();

private:
	cv::VideoCapture* _cap;
	cv::Mat _curr_rgb_frame;
	cv::Mat _prev_rgb_frame;
};

#endif // !VIDEO_HANDLER_H
