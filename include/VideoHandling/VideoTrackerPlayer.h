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
class VideoTrackerPlayer : public QObject
{
    Q_OBJECT

public:
    VideoTrackerPlayer(QMainWindow *image_window, QObject *parent = 0);
    ~VideoTrackerPlayer();

    bool LoadVideo(std::string filename);
    void Play();
    void Stop();
    bool isStopped() const;
    // Video Parameters
    cv::Size GetFrameSize();

public slots:
    void run();

signals:
    // Signal for outputting the frame to be displayed
    void ToBeDisplayed(const QImage &image);
    void pleaseStop();

protected:
    void msleep(int ms);

public:
    void HandleMouseEvent(EventType ev, cv::Point2f obj_coords);

private:
    CvFrameBufferHandler* _FBH_cap;
    PointsManager* _PM_cap;

    QMainWindow* _image_window;

    bool _stop;
    QMutex _mutex;
    QWaitCondition _cond;

    bool _FBH_cap_created;
    int _framerate;
    cv::Mat *_cvFrame;
    QImage _qImg;
};

#endif // VIDEO_TRACKER_PLAYER_H
