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

void PointsManager::ManageNewCoords(EventType ev, cv::Point2f &coords)
{
    bool result = false;
    //std::vector<int> hit_idxs;

    for (auto& point : _points)
    {
        if (point->HitTest(coords))
        {
            result = true;
            if (ev == EventType::MouseClick)
            {
                point->ShowSpectrum();
                //emit DrawSpectrum();
            }
        }
    }

    if (ev != EventType::MouseClick)
        return;

    if (!result)
    {
        AddPoint(coords);
    }
}

void PointsManager::ManageFrames(cv::Mat &frame1, cv::Mat &frame2)
{
    TrackPoints(frame1, frame2, 0);
    CalculateDFourierTransforms();
    DrawPtsAndData(frame2);
}

bool PointsManager::Empty()
{
    return _points.empty();
}

void PointsManager::ClearPoints()
{
    _points.clear();
}

std::vector<QPointer<DataPoint>> &PointsManager::GetPoints()
{
    return _points;
}

void PointsManager::AddPoint(cv::Point2f &point)
{
    // TODO: try push_back and see the difference
    QPointer<DataPoint> p = new DataPoint(point, _sample_rate);
    _points.emplace_back(p);
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

cv::Point2f PointsManager::TrackPoints(cv::Mat &frame1, cv::Mat &frame2, int method_num)
{
    _PT_cap->Track(frame1, frame2, 0);
}

void PointsManager::CalculateDFourierTransforms()
{
    for (auto& point : _points)
    {
        // call DFT for each point
        point->CalculateDFT();
    }
}

void PointsManager::DrawPtsAndData(cv::Mat &frame)
{
    for (auto& point : _points)
    {
        point->DrawPoint(frame, true);
        point->DrawData(frame);
    }
}

// TODO:
//std::vector<double> &PointsManager::GetDFTs()
//{
//}
