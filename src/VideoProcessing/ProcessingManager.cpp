#include "VideoProcessing/ProcessingManager.h"

ProcessingManager::ProcessingManager(QObject *parent) :
    QObject{ parent }
{
    PTCap_ = new PointTracker();
}

ProcessingManager::~ProcessingManager()
{
    delete PTCap_;
}

void ProcessingManager::ManageFrames(cv::Mat& frame1, cv::Mat& frame2, cv::Mat &frameForWrite)
{
    PTCap_->Track(frame1, frame2, OptflowType::SparceToDense);
    frameForWrite = *PTCap_->GetOptflow();
}
