#include "general/VideoHandler.h"

VideoHandler::VideoHandler(const std::string& filename, const std::string& window_name)
	: _video(filename), _window_name(window_name)
{
	//cv::namedWindow(_window_name, cv::WINDOW_NORMAL);
}

void VideoHandler::Play()
{
	while (true)
	{
		cv::Mat frame;
		if (!_video.read(frame))
			break;

		cv::imshow(_window_name, frame);
		if (cv::waitKey(25) == 27)
			break;
	}
}
