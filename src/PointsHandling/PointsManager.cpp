#include "PointsHandling/PointsManager.h"


PointsManager::PointsManager()
{
    // passing a link for a DataPoint vector which is handled in PointsManager and will be tracked in PointTracker
    _PtCap = new PointTracker(&_points);
}

PointsManager::~PointsManager()
{
    // TODO: right now everything looks a little bit motley (if i translated it right).
    // have to make everything more clear and similar. should more be sticking to DRY and KISS
    for (size_t i = _points.size(); i > 0; i--)
    {
        RemovePoint(i - 1);
    }
    delete _PtCap;
}

void PointsManager::UpdateSamplerate(float sample_rate)
{
    _sample_rate = sample_rate;
}

void PointsManager::ManageNewCoords(EventType ev, cv::Point2f &coords)
{
    bool result = false;
    std::vector<size_t> idxsForRemoving;

    for (size_t i = 0; i < _points.size(); i++)
    {
        if (_points[i]->HitTest(coords))
        {
            result = true;
            if (ev == EventType::MouseLeftPressed)
            {
                // TODO: probably change it to slot-signal mechanism
                _points[i]->ShowSpectrum();
            }
            if (ev == EventType::MouseRightPressed)
            {
                idxsForRemoving.push_back(i);
            }
        }
    }

    for (auto &idx : idxsForRemoving)
    {
        RemovePoint(idx);
    }

    if (ev != EventType::MouseLeftPressed)
        return;

    if (!result)
    {
        AddPoint(coords);
    }
}

void PointsManager::ManageFrames(cv::Mat frame1, cv::Mat frame2, cv::Mat &frameForDraw, OptflowType optflowType)
{
    TrackPoints(frame1, frame2, optflowType);
    CalculateDFourierTransforms();
    // TODO: probably i could add a FrameManager class which will to this work
    std::cout << "Preparing useless frame" << std::endl;
    PrepareFrame(frameForDraw, optflowType);
    std::cout << "Started drawing on a frame" << std::endl;
    DrawPtsAndData(frameForDraw);
    std::cout << "Stopped drawing on a frame" << std::endl;
}

bool PointsManager::Empty()
{
    return _points.empty();
}

void PointsManager::ClearPoints()
{
    _points.clear();
}

std::vector<DataPoint*> &PointsManager::GetPoints()
{
    return _points;
}

void PointsManager::AddPoint(cv::Point2f &point)
{
    // TODO: try push_back and see the difference
//    QPointer<DataPoint> p = new DataPoint(point, _sample_rate);
    _points.emplace_back(new DataPoint(point, _sample_rate));
}

void PointsManager::RemovePoint(size_t idx)
{
//    idx = idx - 1;
    if (idx < _points.size())
    {
        delete _points[idx];
        _points.erase(_points.begin() + idx);
    }
}

cv::Point2f PointsManager::TrackPoints(cv::Mat &frame1, cv::Mat &frame2, OptflowType optflowType)
{
    _PtCap->Track(frame1, frame2, optflowType);
}

void PointsManager::CalculateDFourierTransforms()
{
    for (auto& point : _points)
    {
        // call DFT for each point
        point->CalculateDFT();
    }
}

void PointsManager::PrepareFrame(cv::Mat &frame, OptflowType optflowType)
{
    // TODO: make it less hard-coded
    if (optflowType == OptflowType::Calculated)
    {
        std::vector<cv::Mat> frameChannels;
        cv::split(frame, frameChannels);
        std::vector<cv::Mat> outputChannels(1);
        cv::merge(outputChannels, frame);
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
