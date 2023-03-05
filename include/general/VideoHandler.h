#ifndef VIDEO_HANDLER_H
#define VIDEO_HANDLER_H

#include <iostream>
#include "opencv2/opencv.hpp"

class VideoHandler
{
public:
	/*! Конструктор класса, способного проигрывать видео в окне  */
	VideoHandler(const std::string& filename, const std::string& window_name);

	void Play();

private:
	cv::VideoCapture _video;
	std::string _window_name;
};

#endif // !VIDEO_HANDLER_H
