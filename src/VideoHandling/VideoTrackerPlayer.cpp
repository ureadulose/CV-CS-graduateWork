#include "VideoHandling/VideoTrackerPlayer.h"

// for CV waiter implementation
//constexpr double INTERVAL_IN_MS = 25;

VideoTrackerPlayer::VideoTrackerPlayer(QObject *parent) :
    QThread(parent),
    _stop{ true },
    _FBH_cap_created{ false }
{
    _PM_cap = new PointsManager();
    // passing a link for a DataPoint vector which is handled in PointsManager and will be tracked in PointTracker
    _PT_cap = new PointTracker(_PM_cap->GetPoints());
}

VideoTrackerPlayer::~VideoTrackerPlayer()
{
    // Wait til we release VideoCapture from _FBH_cap and wait until run method will be exited
    _mutex.lock();
    _stop = true;

    if (_FBH_cap_created)
        delete _FBH_cap;

    _cond.wakeOne();
    _mutex.unlock();

    delete _PT_cap;
    delete _PM_cap;
}

bool VideoTrackerPlayer::LoadVideo(std::string filename)
{
    _FBH_cap = new CvFrameBufferHandler(filename);
    if (!_FBH_cap->Exists())
        return false;
    _framerate = _FBH_cap->GetFramerate();
    _FBH_cap_created = true;
    return true;
}

void VideoTrackerPlayer::Play()
{
    // isRunning - member of QThread
    if (!isRunning())
    {
        if (isStopped())
            _stop = false;
        start(LowPriority);
    }
}

void VideoTrackerPlayer::Stop()
{
    _stop = true;
}

bool VideoTrackerPlayer::isStopped() const
{
    return this->_stop;
}

void VideoTrackerPlayer::RefreshTrackCoords(cv::Point2f obj_coords)
{
    // TODO: have to recode this later but for now it's like this:
    this->_PM_cap->AddPoint(obj_coords);
}

cv::Size VideoTrackerPlayer::GetFrameSize()
{
    return _FBH_cap->GetFrameSize();
}

void VideoTrackerPlayer::run()
{
    int delay = (1000/_framerate);
    while (!_stop)
    {
        if (!_FBH_cap->ReadFrame())
        {
            _stop = true;
            break;
        }
        _cvFrame = _FBH_cap->GetCurrRgbFrame();

        if (!_PM_cap->Empty())
            {
                _PT_cap->Track(*_FBH_cap->GetPrevRgbFrame(), *_FBH_cap->GetCurrRgbFrame(), 0);
                _PM_cap->DrawPoints(*_FBH_cap->GetCurrRgbFrame());
            }

        cv::cvtColor(*_cvFrame, *_cvFrame, cv::COLOR_BGR2RGB);
        _qImg = QImage((const unsigned char*)(_cvFrame->data),
                      _cvFrame->cols, _cvFrame->rows, QImage::Format_RGB888);

        emit ToBeDisplayed(_qImg);
        this->msleep(delay);
    }
}

void VideoTrackerPlayer::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
