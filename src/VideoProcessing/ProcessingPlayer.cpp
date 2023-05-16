#include "VideoProcessing/ProcessingPlayer.h"

#include "ui/ProcessingWindow.h"

ProcessingPlayer::ProcessingPlayer(QMainWindow *image_window, QObject *parent) :
    VideoTrackerPlayer(image_window)
{
    ProcessManager_ = new ProcessingManager();
}

ProcessingPlayer::~ProcessingPlayer()
{
    delete ProcessManager_;
}

void ProcessingPlayer::run()
{
    int delay = (1000/_framerate);
    while (!_stop)
    {
        cv::Mat frame;
        if (!_FBH_cap->ReadFrame())
        {
            _stop = true;
            break;
        }
        _FBH_cap->GetCurrRgbFrame()->copyTo(_cvFrame);

        // DEBUG
        auto start_time = std::chrono::high_resolution_clock::now();
        // DEBUG END

        ProcessManager_->ManageFrames(*_FBH_cap->GetPrevRgbFrame(), *_FBH_cap->GetCurrRgbFrame(), frame);

        std::vector<cv::Mat> frameChannels;
        cv::split(frame, frameChannels);
        std::vector<cv::Mat> optflowChannels(3);
        optflowChannels[0] = frameChannels[0];
        optflowChannels[1] = frameChannels[1];
        optflowChannels[2] = frameChannels[1];
        cv::merge(optflowChannels, frame);

        _FBH_cap->WriteFrame(frame);

        // DEBUG
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        std::string result = "Time consuming: " + std::to_string(duration) + " us";
        std::cout << result << std::endl;
        // DEBUG END

        cv::cvtColor(_cvFrame, _cvFrame, cv::COLOR_BGR2RGB);
        _qImg = QImage((const unsigned char*)(_cvFrame.data),
                      _cvFrame.cols, _cvFrame.rows, QImage::Format_RGB888);

        emit ToBeDisplayed(_qImg);
        this->msleep(delay);
    }
}


