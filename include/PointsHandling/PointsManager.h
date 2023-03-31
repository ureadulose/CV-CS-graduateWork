#ifndef POINT_MANAGER_H
#define POINT_MANAGER_H

#include "opencv2/core/core.hpp"

#include "include/PointsHandling/DataPoint.h"

class PointsManager
{
public:
    PointsManager();
    ~PointsManager();

    void AddPoint(cv::Point2f& point);
    void RemovePoint(size_t idx);
    bool Empty();
    void ClearPoints();
    void DrawPoints(cv::Mat& frame);
    void CalculateDFourierTransforms();

    std::vector<DataPoint>& GetPoints();

//    TODO:
//    std::vector<double>& GetDFTs();

private:
    std::vector<DataPoint> _points;
};

#endif // POINT_MANAGER_H
