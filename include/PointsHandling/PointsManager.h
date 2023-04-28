#ifndef POINT_MANAGER_H
#define POINT_MANAGER_H

#include "opencv2/core/core.hpp"

#include "include/PointsHandling/DataPoint.h"
#include "include/PointsHandling/PointTracker.h"

// for debug purposes
#include <iostream>

class PointsManager
{
public:
    PointsManager();
    ~PointsManager();

    void UpdateSamplerate(float sample_rate);

    cv::Point2f TrackPoints(cv::Mat& frame1, cv::Mat& frame2, int method_num);
    void AddPoint(cv::Point2f& point);
    void RemovePoint(size_t idx);
    bool Empty();
    void ClearPoints();
    void CalculateDFourierTransforms();
    void DrawPtsAndData(cv::Mat& frame);

    std::vector<DataPoint>& GetPoints();

//    TODO:
//    std::vector<double>& GetDFTs();

private:
    float _sample_rate;

    PointTracker* _PT_cap;
    std::vector<DataPoint> _points;
};

#endif // POINT_MANAGER_H
