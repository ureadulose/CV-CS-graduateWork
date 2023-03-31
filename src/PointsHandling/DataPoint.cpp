#include "include/PointsHandling/DataPoint.h"

DataPoint::DataPoint(cv::Point2f& point) :
    _last_pos{ point }
{
    _radius = 10;
    _color = cv::Scalar(255, 255, 255);
}

DataPoint::~DataPoint()
{

}

void DataPoint::DrawPoint(cv::Mat &frame)
{
    cv::circle(frame, _last_pos, _radius, _color, -1);
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
