#ifndef PROCESSING_PLAYER_H
#define PROCESSING_PLAYER_H

// my headers
#include "VideoHandling/VideoTrackerPlayer.h"
#include "VideoProcessing/ProcessingManager.h"

/*!
* @brief Class is meant to be a shell for the whole app
*/
class ProcessingPlayer : public VideoTrackerPlayer
{
    Q_OBJECT

public:
    ProcessingPlayer(QMainWindow *image_window, QObject *parent = 0);
    ~ProcessingPlayer();

protected:
    void run() override;

private:
    ProcessingManager *ProcessManager_;

};

#endif // PROCESSING_PLAYER_H
