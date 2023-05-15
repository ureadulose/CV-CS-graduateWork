#include "PointsHandling/DataPoint.h"

DataPoint::DataPoint(cv::Point2f& point, float& sample_rate, QObject *parent) :
    QObject(parent),
    _lastPos{ point },
    _radius { 10 },
    _color { cv::Scalar(255, 255, 255) },
    _interacting { false },
    _sampleRate{ sample_rate }
{
    UpdateROI();

    _magnitudes = std::vector<float>();
    _freqs = std::vector<float>();
}

DataPoint::~DataPoint()
{
}

void DataPoint::ShowSpectrum()
{
    _amSpectrDialog = new AmSpectrDialog(_freqs, _magnitudes, _sampleRate);
    QObject::connect(_amSpectrDialog, SIGNAL(finished()), this, SLOT(HideSpectrum()));
    _amSpectrDialog->Startup();
    _amSpectrDialog->show();
}

void DataPoint::DrawPoint(cv::Mat &frame, bool drawArrow)
{
    // draw mark of a point
    if (!drawArrow)
    {
        cv::circle(frame, _lastPos, _radius, _color, -1);
    }
    else
    {
        int offset = _radius * 2;
        cv::Point triangle[3] = {
            cv::Point(_lastPos.x, _lastPos.y),
            cv::Point(_lastPos.x + offset / 2, _lastPos.y - offset),
            cv::Point(_lastPos.x + offset, _lastPos.y - offset / 2)
        };
        cv::fillConvexPoly(frame, triangle, 3, _color);
        cv::circle(frame, cv::Point(_lastPos.x + offset, _lastPos.y - offset), _radius, _color, -1);
    }

    if (_interacting)
    {
        cv::rectangle(frame, _roi, _color, 5);
    }
}

void DataPoint::DrawData(cv::Mat &frame)
{
    putText(
            frame,
            "hz: ",
            cv::Point(_lastPos.x + 15, _lastPos.y),
            font,
            font_scale,
            cv::Scalar(0, 69, 255),
            font_thickness
        );
}

void DataPoint::AddNewPosition(cv::Point2f pos)
{
    _lastPos = pos;
    _positions.emplace_back(pos);
    UpdateROI();

    if (_positions.size() > MAX_POSITIONS_AMOUNT)
    {
        _positions.erase(_positions.begin());
    }
}

void DataPoint::CalculateDFT()
{
    const size_t samples_amount = _positions.size();
    std::vector<cv::Point2f> p2;
    std::vector<cv::Point2f> p1;

    std::vector<cv::Point2f> normalized_positions;
    cv::normalize(_positions, normalized_positions, 0, 1, cv::NORM_MINMAX);

    cv::dft(normalized_positions, _ft);

    // computing two-sided spectrum P2
    for (size_t i = 0; i < _ft.size(); i++)
    {
        p2.push_back(cv::Point2f(_ft[i].x / (float)(samples_amount), _ft[i].y / (float)(samples_amount)));
    }

    // computing single-sided spectrum p1 based on p2 and even-valued signal length
    for (size_t i = 0; i < samples_amount; i++)
    {
        size_t idx = 0;
        idx = (size_t)(((double)(i)) / 2.0 + 1.0);
        p1.push_back(p2[idx]);
    }

    // possible frequencies
    std::vector<float> freqs;
    for(size_t i = 0; i < samples_amount; i++)
    {
        float tmp = _sampleRate * ((float)(i) / 2.f) / (float)(samples_amount);
        freqs.push_back(tmp);
    }

    // computing magnitude
    std::vector<float> magnitudes;
    for (size_t i = 0; i < samples_amount; i++)
    {
        float current_magnitude = sqrt(p1[i].x * p1[i].x + p1[i].y * p1[i].y);
        magnitudes.push_back(current_magnitude);
    }

    _freqs = freqs;
    _magnitudes = magnitudes;

    // finding max value in magnitudes vector
    auto itt_max = std::max_element(magnitudes.begin(), magnitudes.end());
    int max_idx = std::distance(magnitudes.begin(), itt_max);
    // debug
    //std::cout << freqs[max_idx] << std::endl;
}

bool DataPoint::HitTest(cv::Point2f &point)
{
    if (_roi.contains(point))
    {
        _interacting = true;
        return true;
    }
    else
    {
        _interacting = false;
        return false;
    }
}

std::vector<cv::Point2f> &DataPoint::GetPositions()
{
    return _positions;
}

cv::Point2f& DataPoint::GetLastPos()
{
    return _lastPos;
}

float &DataPoint::GetMainFreq()
{
    return _currFrequency;
}

cv::Rect &DataPoint::GetRoi()
{
    return _roi;
}

void DataPoint::HideSpectrum()
{
    delete _amSpectrDialog;
}

void DataPoint::UpdateROI()
{
    _roi = cv::Rect(
                cv::Point(_lastPos.x - INTERACTION_OFFSET, _lastPos.y - INTERACTION_OFFSET),
                cv::Point(_lastPos.x + INTERACTION_OFFSET, _lastPos.y + INTERACTION_OFFSET)
                );
}
