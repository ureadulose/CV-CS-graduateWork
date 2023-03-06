#ifndef TRACKER_BODY_H
#define TRACKER_BODY_H

// my headers
#include "general/VideoHandler.h"
#include "general/PointTracker.h"

/*!
* @brief Класс предназначен в качестве оболочки для всей программы
*/
class TrackerBody
{
public:
	TrackerBody(std::string& filename, std::string& window_name);
	~TrackerBody();

	bool Run();

private:
	static void onMouseClick(int event, int x, int y, int flags, void* userdata);


private:
	std::string _filename;
	std::string _window_name;

	VideoHandler* _VH_cap;
	PointTracker* _PT_cap;

	cv::Point2f _obj_coords;

	bool _onPause;
};

#endif // !TRACKER_BODY_H