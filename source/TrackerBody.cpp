#include "general/TrackerBody.h"

constexpr double INTERVAL_IN_MS = 25;

TrackerBody::TrackerBody(std::string& filename, std::string& window_name)
	: _filename(filename), _window_name(window_name), _onPause(false)
{
	_VH_cap = new VideoHandler(_filename);
	cv::namedWindow(_window_name, cv::WINDOW_NORMAL);
}

TrackerBody::~TrackerBody()
{
	delete _VH_cap;
	cv::destroyAllWindows();
}

bool TrackerBody::Run()
{
	while (true)
	{
		if (!_onPause)
		{
			_VH_cap->ReadFrame();
		}
		cv::imshow(_window_name, _VH_cap->GetCurrRgbFrame());
		int key = cv::waitKey(INTERVAL_IN_MS);
		switch (key)
		{
		case 27:
			return false;
		case 32:
			_onPause = !_onPause;
		}
	}
	return false;
}
