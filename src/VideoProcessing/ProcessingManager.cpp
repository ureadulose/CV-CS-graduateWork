#include "VideoProcessing/ProcessingManager.h"

ProcessingManager::ProcessingManager(QObject *parent) :
    QObject{ parent }
{
    PTCap_ = new PointTracker(nullptr);
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

void ProcessingManager::CombineFrames(cv::Mat optflow, cv::Mat frame, cv::Mat &frameForWrite)
{
    // create 4-channel cv::Mat
    frameForWrite = cv::Mat(frame.rows, frame.cols, CV_8UC(4));

    std::vector<cv::Mat> optflowChannels;
    std::vector<cv::Mat> frameChannels;
    std::vector<cv::Mat> frameForWriteChannels;
    cv::split(optflow, optflowChannels);
    cv::split(frame, frameChannels);
    cv::split(frameForWrite, frameForWriteChannels);

    frameForWriteChannels[0] = frameChannels[0];
    frameForWriteChannels[1] = optflowChannels[0];
    frameForWriteChannels[2] = optflowChannels[1];

    cv::merge(frameForWriteChannels, frameForWrite);
}
