#ifndef DATA_POINT_H
#define DATA_POINT_H

#include "opencv2/core/core.hpp"
#include <opencv2/imgproc.hpp>

#include "QCustomPlot/PlotThread.h"
#include <QObject>

// for debug purposes
#include <iostream>

const int MAX_POSITIONS_AMOUNT = 512;
const int INTERACTION_OFFSET = 16;
const int font = cv::FONT_HERSHEY_PLAIN;
const double font_scale = 1.5;
const int font_thickness = 2;

class DataPoint : public QObject
{
    Q_OBJECT

public:
    DataPoint(cv::Point2f& point, float& sample_rate, QObject *parent = nullptr);
    ~DataPoint();

    void ShowSpectrum();

    void DrawPoint(cv::Mat& frame, bool drawArrow = false);
    void DrawData(cv::Mat& frame);

    // try &
    void AddNewPosition(cv::Point2f pos);

    void CalculateDFT();

    bool HitTest(cv::Point2f& point);

    cv::Point2f& GetLastPos();
    /*!
     * \brief Returns frequency with maximum amplitude from DFT
     * \return frequency
     */
    float& GetMainFreq();
    cv::Rect& GetRoi();

private slots:
    void FreePlotThread();

private:
    void UpdateROI();

private:
    PlotThread *_plot_thread;

    cv::Point2f _last_pos;
    std::vector<cv::Point2f> _positions;

    int _radius;
    cv::Scalar _color;
    cv::Rect _roi;
    bool _interacting;

    float _sample_rate;
    std::vector<cv::Point2f> _ft;
    float _curr_frequency;

    // probably temporary
    std::vector<float> _magnitudes;
    std::vector<float> _freqs;
};

#endif // DATA_POINT_H
