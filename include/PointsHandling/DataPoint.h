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
    void DrawData(cv::Mat& frame);

    void AddNewPosition(cv::Point2f pos);
    cv::Point2f& GetLastPos();

    void CalculateDFT();

    /*!
     * \brief Returns frequency with maximum amplitude from DFT
     * \return frequency
     */
    float GetMainFreq();

private:

private:
    cv::Point2f _last_pos;
    std::vector<cv::Point2f> _positions;

    int _radius;
    cv::Scalar _color;

    std::vector<double> _ft;
    float _curr_frequency;
};

#endif // DATA_POINT_H
