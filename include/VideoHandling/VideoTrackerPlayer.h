#ifndef VIDEO_TRACKER_PLAYER_H
#define VIDEO_TRACKER_PLAYER_H

// my headers
#include "PointsHandling/PointsManager.h"
#include "VideoHandling/CvFrameBufferHandler.h"
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
    void SetPosition(int value);

signals:
    // Signal for outputting the frame to be displayed
    void ToBeDisplayed(const QImage &image);

protected:
    virtual void run();
    void msleep(int ms);

protected:
    CvFrameBufferHandler* _FbhCap; // protected:
    CvFrameBufferHandler* _FBH_optflow_cap; // protected:
    int _framerate; //protected:
    bool _stop; // protected:
    cv::Mat _cvFrame; // protected:
    QImage _qImg; // protected:

private:
    PointsManager* _PmCap;
    bool _precalcVideo;
    OptflowType _optflowType;
    QMainWindow* _imageWindow;
    QMutex _mutex;
    QWaitCondition _cond;
    bool _FbhCapCreated;
    bool _FbhOptflowCapCreated;
};

#endif // VIDEO_TRACKER_PLAYER_H
