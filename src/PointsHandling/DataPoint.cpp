#include "PointsHandling/DataPoint.h"

DataPoint::DataPoint(cv::Point2f& point, float& sample_rate) :
    _last_pos{ point },
    _sample_rate{ sample_rate }
{
    _radius = 10;
    _color = cv::Scalar(255, 255, 255);
}

DataPoint::~DataPoint()
{

}

void DataPoint::DrawPoint(cv::Mat &frame, bool drawArrow)
{
    // draw mark of a point
    if (!drawArrow)
    {
        cv::circle(frame, _last_pos, _radius, _color, -1);
    }
    else
    {
        int offset = _radius * 2;
        cv::Point triangle[3] = {
            cv::Point(_last_pos.x, _last_pos.y),
            cv::Point(_last_pos.x + offset / 2, _last_pos.y - offset),
            cv::Point(_last_pos.x + offset, _last_pos.y - offset / 2)
        };
        cv::fillConvexPoly(frame, triangle, 3, _color);
        cv::circle(frame, cv::Point(_last_pos.x + offset, _last_pos.y - offset), _radius, _color, -1);
    }

    // draw current frequency of a point

}

void DataPoint::DrawData(cv::Mat &frame)
{
    // text parameters
    // TODO: replace it to a more suitable place
    int font = cv::FONT_HERSHEY_PLAIN;
    double font_scale = 1.5;
    int thickness = 2;

    putText(
            frame,
            "hz: ",
            cv::Point(_last_pos.x + 15, _last_pos.y),
            font,
            font_scale,
            cv::Scalar(0, 69, 255),
            thickness
        );
}

void DataPoint::AddNewPosition(cv::Point2f pos)
{
    _last_pos = pos;
    _positions.emplace_back(pos);

    if (_positions.size() > MAX_POSITIONS_AMOUNT)
    {
        _positions.erase(_positions.begin());
    }
}

cv::Point2f& DataPoint::GetLastPos()
{
    return _last_pos;
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
        float tmp = _sample_rate * ((float)(i) / 2.f) / (float)(samples_amount);
        freqs.push_back(tmp);
    }

    // computing magnitude
    std::vector<float> magnitudes;
    for (size_t i = 0; i < samples_amount; i++)
    {
        float current_magnitude = sqrt(p1[i].x * p1[i].x + p1[i].y * p1[i].y);
        magnitudes.push_back(current_magnitude);
    }

    // finding max value in magnitudes vector
    auto itt_max = std::max_element(magnitudes.begin(), magnitudes.end());
    int max_idx = std::distance(magnitudes.begin(), itt_max);
    std::cout << freqs[max_idx] << std::endl;
}

float DataPoint::GetMainFreq()
{
    return _curr_frequency;
}
