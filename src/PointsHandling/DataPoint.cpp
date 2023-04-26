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
}

void DataPoint::AddPos(cv::Point2f pos)
{
    _last_pos = pos;
    _positions.emplace_back(pos);
}

cv::Point2f& DataPoint::GetLastPos()
{
    return _last_pos;
}

std::vector<double> &DataPoint::GetDFourierTransform()
{
    if (_ft.empty())
    {
        CalculateDFourierTransform();
    }
    return _ft;
}

void DataPoint::CalculateDFourierTransform()
{
    // TODO: Implement fourier transform calculation for this point
    //       and store the result in _ft member variable
}
