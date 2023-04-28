#include "PointsHandling/PointsManager.h"


PointsManager::PointsManager()
{
    // passing a link for a DataPoint vector which is handled in PointsManager and will be tracked in PointTracker
    _PT_cap = new PointTracker(_points);
}

PointsManager::~PointsManager()
{
    delete _PT_cap;
}

void PointsManager::UpdateSamplerate(float sample_rate)
{
    _sample_rate = sample_rate;
}

cv::Point2f PointsManager::TrackPoints(cv::Mat &frame1, cv::Mat &frame2, int method_num)
{
    _PT_cap->Track(frame1, frame2, 0);
}

void PointsManager::AddPoint(cv::Point2f &point)
{
    // TODO: try push_back and see the difference
    _points.emplace_back(point, _sample_rate);
}

void PointsManager::RemovePoint(size_t idx)
{
    if (idx < _points.size())
    {
        _points.erase(_points.begin() + idx);
    }
    std::cout << "capacity: " << _points.capacity() << std::endl;
    std::cout << "max_size: " << _points.max_size() << std::endl;
    std::cout << "current size: " << _points.size() << std::endl;
}

bool PointsManager::Empty()
{
    return _points.empty();
}

void PointsManager::ClearPoints()
{
    _points.clear();
}

void PointsManager::CalculateDFourierTransforms()
{
    for (auto& point : _points)
    {
        // call DFT for each point
        point.CalculateDFT();
        //std::cout << "calculating DFT..." << std::endl;
    }
}

void PointsManager::DrawPtsAndData(cv::Mat &frame)
{
    for (auto& point : _points)
    {
        point.DrawPoint(frame, true);
        point.DrawData(frame);
    }
}

std::vector<DataPoint> &PointsManager::GetPoints()
{
    return _points;
}

// TODO:
//std::vector<double> &PointsManager::GetDFTs()
//{
//}
