#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "VideoHandling/VideoTrackerPlayer.h"
#include "MyEnums.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ImageWindow; }
QT_END_NAMESPACE

class ImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = nullptr);
    ~ImageWindow();

private:
    // refactor this
    cv::Point2f MapToImageCoords(QSize map_size, cv::Size image_size, QPointF src_coords);

signals:
    void NewClick(EventType ev, const cv::Point2f coordinates);
    void NewMousePos(EventType ev, const cv::Point2f coordinates);

private slots:
    // Display video frame in player UI
    void updatePlayerUI(QImage img);

    // Slot for the load video push button
    void on_pushButton_clicked();

    // Slot for the play push button
    void on_pushButton_2_clicked();

    // Slot for getting current mouse position on a VideoFrame
    void MouseCurrentPos();

    void MousePressed();

    void MouseLeftFrame();

private:
    Ui::ImageWindow *ui;
    VideoTrackerPlayer *VTPlayer;
    QThread *playerThread;
};
#endif // IMAGEWINDOW_H
