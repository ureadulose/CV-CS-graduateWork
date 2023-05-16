#include "VideoHandling/VideoTrackerPlayer.h"

#include "ui/ImageWindow.h"

VideoTrackerPlayer::VideoTrackerPlayer(QMainWindow *image_window, QObject *parent) :
    QThread(parent),
    _stop{ true },
    precalcVideo_{ false },
    optflowType_{ OptflowType::SparseLucasKanade },
    _image_window{ image_window },
    _FBH_cap_created{ false },
    _FBH_optflow_cap_created{ false }
{
    _PM_cap = new PointsManager();

    QObject::connect(_image_window, SIGNAL(NewClick(EventType,cv::Point2f)),
                     this, SLOT(HandleMouseEvent(EventType,cv::Point2f)));
    QObject::connect(_image_window, SIGNAL(NewMousePos(EventType,cv::Point2f)),
                     this, SLOT(HandleMouseEvent(EventType,cv::Point2f)));
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

    delete _PM_cap;
}

bool VideoTrackerPlayer::LoadVideo(std::string filename)
{
    // reset the Frame Buffer Handler
    if (_FBH_cap_created)
    {
        delete _FBH_cap;
        _FBH_cap_created = false;
    }

    _FBH_cap = new CvFrameBufferHandler(filename);
    if (!_FBH_cap->Exists())
        return false;

    _framerate = _FBH_cap->GetFramerate();
    _PM_cap->UpdateSamplerate(_framerate);
    _FBH_cap_created = true;
    precalcVideo_ = false;

    return true;
}

bool VideoTrackerPlayer::LoadOptflow(std::string filename)
{
    _FBH_optflow_cap = new CvFrameBufferHandler(filename);
    if (!_FBH_optflow_cap->Exists())
        return false;

    _FBH_optflow_cap_created = true;
    precalcVideo_ = true;
    optflowType_ = OptflowType::Calculated;

    return true;
}

void VideoTrackerPlayer::Play()
{
    // isRunning - member of QThread
    if (!isRunning())
        {
            if (isStopped())
                _stop = false;
            start(QThread::LowPriority);
        }
}

void VideoTrackerPlayer::Stop()
{
    _stop = true;
    emit pleaseStop();
}

bool VideoTrackerPlayer::isStopped() const
{
    return this->_stop;
}

cv::Size VideoTrackerPlayer::GetFrameSize()
{
    return _FBH_cap->GetFrameSize();
}

void VideoTrackerPlayer::HandleMouseEvent(EventType ev, cv::Point2f obj_coords)
{
    this->_PM_cap->ManageNewCoords(ev, obj_coords);
}

void VideoTrackerPlayer::run()
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

        if (!_PM_cap->Empty())
            {
                // DEBUG
                auto start_time = std::chrono::high_resolution_clock::now();
                // DEBUG END

                if (!_FBH_optflow_cap_created)
                {
                    _PM_cap->ManageFrames(*_FBH_cap->GetPrevRgbFrame(), *_FBH_cap->GetCurrRgbFrame(), _cvFrame, optflowType_);
                }
                else
                {
                    !_FBH_optflow_cap->ReadFrame();
                    _PM_cap->ManageFrames(*_FBH_optflow_cap->GetPrevRgbFrame(), *_FBH_optflow_cap->GetCurrRgbFrame(), _cvFrame, optflowType_);
                }

                // DEBUG
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
                std::string result = "Time consuming: " + std::to_string(duration) + " us";
                std::cout << result << std::endl;
                // DEBUG END
            }

        cv::cvtColor(_cvFrame, _cvFrame, cv::COLOR_BGR2RGB);
        _qImg = QImage((const unsigned char*)(_cvFrame.data),
                      _cvFrame.cols, _cvFrame.rows, QImage::Format_RGB888);

        emit ToBeDisplayed(_qImg);
        this->msleep(delay);
    }
}

void VideoTrackerPlayer::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
