#ifndef POINT_MANAGER_H
#define POINT_MANAGER_H

#include "opencv2/core/core.hpp"

#include "include/PointsHandling/DataPoint.h"
#include "include/PointsHandling/PointTracker.h"
#include "EventType.h"

// for debug purposes
#include <iostream>

class PointsManager
{
public:
    PointsManager();
    ~PointsManager();

    void UpdateSamplerate(float sample_rate);

    cv::Point2f TrackPoints(cv::Mat& frame1, cv::Mat& frame2, int method_num);
    void ManageNewCoords(EventType ev, cv::Point2f& coords);
    bool Empty();
    void ClearPoints();
    void CalculateDFourierTransforms();
    void DrawPtsAndData(cv::Mat& frame);

    std::vector<DataPoint>& GetPoints();

//    TODO:
//    std::vector<double>& GetDFTs();

private:
    void AddPoint(cv::Point2f& point);
    void RemovePoint(size_t idx);

private:
    float _sample_rate;

    PointTracker* _PT_cap;
    std::vector<DataPoint> _points;
};

#endif // POINT_MANAGER_H
