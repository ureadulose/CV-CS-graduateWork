#ifndef PROCESSING_MANAGER_H
#define PROCESSING_MANAGER_H

// qt headers
#include <QObject>

// opencv headers
#include <opencv2/imgproc.hpp>
#include <opencv2/optflow.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/highgui.hpp>

// my headers
#include "MyEnums.h"
#include "PointsHandling/PointTracker.h"

/*!
* @brief Class is meant to be a shell for the whole app
*/
class ProcessingManager : public QObject
{
    Q_OBJECT

public:
    ProcessingManager(QObject *parent = 0);
    ~ProcessingManager();

    void ManageFrames(cv::Mat &frame1, cv::Mat &frame2, cv::Mat &frameForWrite);
    void CombineFrames(cv::Mat optflow, cv::Mat frame, cv::Mat &frameForWrite);

private:
    PointTracker *PTCap_;

};

#endif // PROCESSING_MANAGER_H
