#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "VideoProcessing/ProcessingPlayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProcessingWindow; }
QT_END_NAMESPACE

class ProcessingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProcessingWindow(QWidget *parent = nullptr);
    ~ProcessingWindow();

private:
    cv::Point2f MapToImageCoords(QSize map_size, cv::Size image_size, QPointF src_coords);

private slots:
    // Display video frame in player UI
    void updatePlayerUI(QImage img);

    // Slot for the load video push button
    void on_pushButton_clicked();

    // Slot for the play push button
    void on_pushButton_2_clicked();

    void closeEvent(QCloseEvent *ev);

private:
    Ui::ProcessingWindow *ui;
    ProcessingPlayer *ProcessPlayer;
};
#endif // IMAGEWINDOW_H
