#include "PointsHandling/PointsManager.h"


PointsManager::PointsManager()
{

}

PointsManager::~PointsManager()
{

}

void PointsManager::AddPoint(cv::Point2f &point)
{
    // TODO: try push_back and see the difference
    _points.emplace_back(point);
}

void PointsManager::RemovePoint(size_t idx)
{
    if (idx < _points.size())
    {
        _points.erase(_points.begin() + idx);
    }
}

bool PointsManager::Empty()
{
    return _points.empty();
}

void PointsManager::ClearPoints()
{
    _points.clear();
}

void PointsManager::DrawPoints(cv::Mat &frame)
{
    for (auto& point : _points)
    {
        point.DrawPoint(frame);
    }
}

void PointsManager::CalculateDFourierTransforms()
{

}

std::vector<DataPoint> &PointsManager::GetPoints()
{
    return _points;
}

// TODO:
//std::vector<double> &PointsManager::GetDFTs()
//{
//}
