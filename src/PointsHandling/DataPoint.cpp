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
    const int samples_amount = _positions.size();

    // Creating coordinates matrix
    cv::Mat mat_positions(samples_amount, 2, CV_32FC2);

    for (int i = 0; i < samples_amount; i++)
    {
        mat_positions.at<float>(i, 0) = _positions[i].x;
        mat_positions.at<float>(i, 1) = _positions[i].y;
    }

    cv::Mat mat_transformed;
    cv::dft(mat_positions, mat_transformed, cv::DFT_COMPLEX_OUTPUT);

    cv::Mat mat_magnitude;
    cv::magnitude(mat_transformed.col(0), mat_transformed.col(1), mat_magnitude);

    std::vector<cv::Mat> channels;
    cv::split(mat_magnitude, channels);

    double max_val_x, max_val_y;
    cv::minMaxLoc(channels[0], nullptr, &max_val_x);
    cv::minMaxLoc(channels[1], nullptr, &max_val_y);
    double freq_x = max_val_x * _sample_rate / samples_amount;
    double freq_y = max_val_y * _sample_rate / samples_amount;

    std::cout << "curr frequency: " << _curr_frequency << std::endl;
}

float DataPoint::GetMainFreq()
{
    return _curr_frequency;
}
