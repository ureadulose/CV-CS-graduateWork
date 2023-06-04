#ifndef DATA_POINT_H
#define DATA_POINT_H

#include "opencv2/core/core.hpp"
#include <opencv2/imgproc.hpp>

#include "ui/AmSpectrDialog.h"

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

    bool ShowSpectrum();

    void DrawPoint(cv::Mat& frame, bool drawArrow = false);
    void DrawData(cv::Mat& frame);

    // try &
    void AddNewPosition(cv::Point2f pos);

    void CalculateDFT();

    bool HitTest(cv::Point2f& point);

    std::vector<cv::Point2f>& GetPositions();
    cv::Point2f& GetLastPos();
    /*!
     * \brief Returns frequency with maximum amplitude from DFT
     * \return frequency
     */
    float& GetMainFreq();
    cv::Rect& GetRoi();

private slots:
    void HideSpectrum();

private:
    void UpdateROI();

private:
    AmSpectrDialog *_amSpectrDialog;

    cv::Point2f _lastPos;
    std::vector<cv::Point2f> _positions;

    int _radius;
    cv::Scalar _color;
    cv::Rect _roi;
    bool _interacting;

    float _sampleRate;
    std::vector<cv::Point2f> _ft;
    float _maxMagnitude;

    // probably temporary
    std::vector<float> _magnitudes;
    std::vector<float> _magnitudesHor;
    std::vector<float> _magnitudesVer;
    std::vector<float> _freqs;
};

#endif // DATA_POINT_H
