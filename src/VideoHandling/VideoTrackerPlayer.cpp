#include "VideoHandling/VideoTrackerPlayer.h"

VideoTrackerPlayer::VideoTrackerPlayer(QMainWindow *imageWindow, QObject *parent) :
    QThread(parent),
    _stop{ true },
    _precalcVideo{ false },
    _optflowType{ OptflowType::SparseLucasKanade },
    _imageWindow{ imageWindow },
    _FbhCapCreated{ false },
    _FbhOptflowCapCreated{ false }
{
    _PmCap = new PointsManager();

    QObject::connect(_imageWindow, SIGNAL(NewClick(EventType,cv::Point2f)),
                     this, SLOT(HandleMouseEvent(EventType,cv::Point2f)));
    QObject::connect(_imageWindow, SIGNAL(NewMousePos(EventType,cv::Point2f)),
                     this, SLOT(HandleMouseEvent(EventType,cv::Point2f)));
}

VideoTrackerPlayer::~VideoTrackerPlayer()
{
    // Wait til we release VideoCapture from _FBH_cap and wait until run method will be exited
    _mutex.lock();
    _stop = true;
    std::cout << "VideoTrackerPlayer Destructor" << std::endl;
    if (_FbhCapCreated)
        delete _FbhCap;

    _cond.wakeOne();
    _mutex.unlock();

    delete _PmCap;
}

bool VideoTrackerPlayer::LoadVideo(std::string filename)
{
    // reset the Frame Buffer Handler
    if (_FbhCapCreated)
    {
        delete _FbhCap;
        _FbhCapCreated = false;
    }

    _FbhCap = new CvFrameBufferHandler(filename);
    if (!_FbhCap->Exists())
        return false;

    _framerate = _FbhCap->GetFramerate();
    _PmCap->UpdateSamplerate(_framerate);
    _FbhCapCreated = true;
    _precalcVideo = false;

    return true;
}

bool VideoTrackerPlayer::LoadOptflow(std::string filename)
{
    _FBH_optflow_cap = new CvFrameBufferHandler(filename);
    if (!_FBH_optflow_cap->Exists())
        return false;

    _FbhOptflowCapCreated = true;
    _precalcVideo = true;
    _optflowType = OptflowType::Calculated;

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
}

bool VideoTrackerPlayer::isStopped() const
{
    return this->_stop;
}

cv::Size VideoTrackerPlayer::GetFrameSize()
{
    return _FbhCap->GetFrameSize();
}

void VideoTrackerPlayer::HandleMouseEvent(EventType ev, cv::Point2f obj_coords)
{
    this->_PmCap->ManageNewCoords(ev, obj_coords);
}

void VideoTrackerPlayer::SetPosition(int value)
{
    std::cout << "cum " << value << std::endl;
}

void VideoTrackerPlayer::run()
{
    int delay = (1000/_framerate);
    while (!_stop)
    {
        cv::Mat frame;
        if (!_FbhCap->ReadFrame())
        {
            _stop = true;
            break;
        }
        _FbhCap->GetCurrRgbFrame()->copyTo(_cvFrame);

        if (!_PmCap->Empty())
            {
                // DEBUG
                auto start_time = std::chrono::high_resolution_clock::now();
                // DEBUG END

                if (!_FbhOptflowCapCreated)
                {
                    _PmCap->ManageFrames(*_FbhCap->GetPrevRgbFrame(), *_FbhCap->GetCurrRgbFrame(), _cvFrame, _optflowType);
                }
                else
                {
                    !_FBH_optflow_cap->ReadFrame();
                    _PmCap->ManageFrames(*_FBH_optflow_cap->GetPrevRgbFrame(), *_FBH_optflow_cap->GetCurrRgbFrame(), _cvFrame, _optflowType);
                }

                // DEBUG
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
                std::string result = "Time consuming: " + std::to_string(duration) + " us";
                //std::cout << result << std::endl;
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
