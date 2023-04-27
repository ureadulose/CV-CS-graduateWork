#include "PointsHandling/DataPoint.h"

DataPoint::DataPoint(cv::Point2f& point) :
    _last_pos{ point }
{
    _radius = 10;
    _color = cv::Scalar(255, 255, 255);
}

DataPoint::~DataPoint()
{

}

void DataPoint::DrawPoint(cv::Mat &frame, bool drawArrow)
{
    // draw mark of a point
    if (!drawArrow)
    {
        cv::circle(frame, _last_pos, _radius, _color, -1);
    }
    else
    {
        int offset = _radius * 2;
        cv::Point triangle[3] = {
            cv::Point(_last_pos.x, _last_pos.y),
            cv::Point(_last_pos.x + offset / 2, _last_pos.y - offset),
            cv::Point(_last_pos.x + offset, _last_pos.y - offset / 2)
        };
        cv::fillConvexPoly(frame, triangle, 3, _color);
        cv::circle(frame, cv::Point(_last_pos.x + offset, _last_pos.y - offset), _radius, _color, -1);
    }

    // draw current frequency of a point

}

void DataPoint::DrawData(cv::Mat &frame)
{
    // text parameters
    // TODO: replace it to a more suitable place
    int font = cv::FONT_HERSHEY_PLAIN;
    double font_scale = 1.5;
    int thickness = 2;

    putText(
            frame,
            "hz: ",
            cv::Point(_last_pos.x + 15, _last_pos.y),
            font,
            font_scale,
            cv::Scalar(0, 69, 255),
            thickness
        );
}

void DataPoint::AddNewPosition(cv::Point2f pos)
{
    _last_pos = pos;
    _positions.emplace_back(pos);
}

cv::Point2f& DataPoint::GetLastPos()
{
    return _last_pos;
}

void DataPoint::CalculateDFT()
{
    if (_ft.empty())
    {
        // actions for first usage of a point
    }
}

float DataPoint::GetMainFreq()
{
    return _curr_frequency;
}
