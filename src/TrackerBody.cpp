#include "general/TrackerBody.h"

constexpr double INTERVAL_IN_MS = 25;

TrackerBody::TrackerBody(std::string& filename, std::string& window_name)
	: _filename(filename), _window_name(window_name), _onPause(false)
{
	_VH_cap = new VideoHandler(_filename);
	_PT_cap = new PointTracker();

	_obj_coords = cv::Point2f(0.f, 0.f);

	cv::namedWindow(_window_name, cv::WINDOW_NORMAL);

	cv::setMouseCallback(_window_name, onMouseClick, this);
}

TrackerBody::~TrackerBody()
{
	delete _VH_cap;
    delete _PT_cap;
	cv::destroyAllWindows();
}

bool TrackerBody::Run()
{
	while (true)
	{
		if (!_onPause)
		{
			if (!_VH_cap->ReadFrame())
				break;
		}

		if (_obj_coords.x != 0.f && _obj_coords.y != 0.f)
		{
            _PT_cap->Track(*_VH_cap->GetPrevRgbFrame(), *_VH_cap->GetCurrRgbFrame(), _obj_coords, 0);
			_PT_cap->DrawPointOnAFrame(*_VH_cap->GetCurrRgbFrame(), _obj_coords);
		}



		cv::imshow(_window_name, *_VH_cap->GetCurrRgbFrame());

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

void TrackerBody::onMouseClick(int event, int x, int y, int flags, void* userdata)
{
	TrackerBody* TB = reinterpret_cast<TrackerBody*>(userdata);

    // Event handler
    if (event == cv::EVENT_LBUTTONDOWN)
	{
		std::cout << "Mouse clicked at (" << x << ", " << y << ")" << std::endl;
		TB->_obj_coords = cv::Point2i(x, y);
	}
}
