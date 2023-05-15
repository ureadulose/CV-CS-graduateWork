#ifndef POINT_MANAGER_H
#define POINT_MANAGER_H

#include "opencv2/core/core.hpp"

#include "include/PointsHandling/DataPoint.h"
#include "include/PointsHandling/PointTracker.h"
#include "MyEnums.h"

// for debug purposes
#include <iostream>

class PointsManager
{
public:
    PointsManager();
    ~PointsManager();

    void UpdateSamplerate(float sample_rate);

    void ManageNewCoords(EventType ev, cv::Point2f& coords);
    void ManageFrames(cv::Mat frame1, cv::Mat frame2, cv::Mat &frameForDraw);
    bool Empty();
    void ClearPoints();

    std::vector<QPointer<DataPoint>>& GetPoints();

private:
    void AddPoint(cv::Point2f& point);
    void RemovePoint(size_t idx);

    cv::Point2f TrackPoints(cv::Mat& frame1, cv::Mat& frame2, int method_num);
    void CalculateDFourierTransforms();
    void DrawPtsAndData(cv::Mat& frame);

private:
    float _sample_rate;

    PointTracker* _PT_cap;
    std::vector<QPointer<DataPoint>> _points;
};

#endif // POINT_MANAGER_H
