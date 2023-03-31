#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "VideoHandling/VideoTrackerPlayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    cv::Point2f MapToImageCoords(QSize map_size, cv::Size image_size, QPointF src_coords);

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
    Ui::MainWindow *ui;
    VideoTrackerPlayer *VTPlayer;
};
#endif // IMAGEWINDOW_H
