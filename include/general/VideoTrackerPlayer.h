#ifndef VIDEO_TRACKER_PLAYER_H
#define VIDEO_TRACKER_PLAYER_H

// my headers
#include "general/CvFrameBufferHandler.h"
#include "general/PointTracker.h"

#include <QImage>

/*!
* @brief Class is meant to be a shell for the whole app
*/
class VideoTrackerPlayer : public QThread
{
    Q_OBJECT

public:
    VideoTrackerPlayer(QObject *parent = 0);
    ~VideoTrackerPlayer();

    bool LoadVideo(std::string filename);
    void Play();
    void Stop();
    bool isStopped() const;

    void RefreshTrackCoords(cv::Point2f obj_coords);

    // Video Parameters
    cv::Size GetFrameSize();

signals:
    // Signal for outputting the frame to be displayed
    void ToBeDisplayed(const QImage &image);

protected:
    void run();
    void msleep(int ms);

//private:
//	static void onMouseClick(int event, int x, int y, int flags, void* userdata);


private:
    CvFrameBufferHandler* _FBH_cap;
    PointTracker* _PT_cap;

    cv::Point2f _obj_coords;

    bool _stop;
    QMutex _mutex;
    QWaitCondition _cond;

    bool _FBH_cap_created;
    int _framerate;
    cv::Mat *_cvFrame;
    QImage _qImg;
};

#endif // VIDEO_TRACKER_PLAYER_H
