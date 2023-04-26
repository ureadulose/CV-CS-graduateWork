#ifndef DATA_POINT_H
#define DATA_POINT_H

#include "opencv2/core/core.hpp"
#include <opencv2/imgproc.hpp>

class DataPoint
{
public:
    DataPoint(cv::Point2f& point);
    ~DataPoint();

    void DrawPoint(cv::Mat& frame, bool drawArrow = false);
    void AddPos(cv::Point2f pos);
    cv::Point2f& GetLastPos();

    std::vector<double>& GetDFourierTransform();

private:
    void CalculateDFourierTransform();

private:
    cv::Point2f _last_pos;
    std::vector<cv::Point2f> _positions;

    int _radius;
    cv::Scalar _color;

    std::vector<double> _ft;
    float _curr_frequency;
};

#endif // DATA_POINT_H
