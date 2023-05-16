#ifndef VIDEO_TRACKER_PLAYER_H
#define VIDEO_TRACKER_PLAYER_H

// my headers
#include "VideoHandling/CvFrameBufferHandler.h"
#include "PointsHandling/PointsManager.h"
#include "MyEnums.h"

#include <QImage>
#include <QMainWindow>

// for debug purposes
#include <chrono>

/*!
* @brief Class is meant to be a shell for the whole app
*/
class VideoTrackerPlayer : public QThread
{
    Q_OBJECT

public:
    VideoTrackerPlayer(QMainWindow *image_window, QObject *parent = 0);
    ~VideoTrackerPlayer();

    bool LoadVideo(std::string filename);
    bool LoadOptflow(std::string filename);
    void Play();
    void Stop();
    bool isStopped() const;
    // Video Parameters
    cv::Size GetFrameSize();

public slots:
    void HandleMouseEvent(EventType ev, cv::Point2f obj_coords);

signals:
    // Signal for outputting the frame to be displayed
    void ToBeDisplayed(const QImage &image);
    void pleaseStop();

protected:
    virtual void run();
    void msleep(int ms);

protected:
    CvFrameBufferHandler* _FBH_cap; // protected:
    CvFrameBufferHandler* _FBH_optflow_cap; // protected:
    int _framerate; //protected:
    bool _stop; // protected:
    cv::Mat _cvFrame; // protected:
    QImage _qImg; // protected:

private:
    PointsManager* _PM_cap;
    bool precalcVideo_;
    OptflowType optflowType_;
    QMainWindow* _image_window;
    QMutex _mutex;
    QWaitCondition _cond;
    bool _FBH_cap_created;
    bool _FBH_optflow_cap_created;
};

#endif // VIDEO_TRACKER_PLAYER_H
