#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "general/VideoTrackerPlayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Display video frame in player UI
    void updatePlayerUI(QImage img);

    // Slot for the load video push button
    void on_pushButton_clicked();

    // Slot for the play push button
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    VideoTrackerPlayer *VTPlayer;
};
#endif // IMAGEWINDOW_H
