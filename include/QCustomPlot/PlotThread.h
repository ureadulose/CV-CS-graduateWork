#ifndef PLOT_THREAD_H
#define PLOT_THREAD_H

#include <QThread>

#include "ui/AmSpectrDialog.h"

class PlotThread : public QThread
{
    Q_OBJECT

public:
    PlotThread(std::vector<float> &x, std::vector<float> &y, int framerate, QObject *parent = nullptr);

    void ShowDialog();
    void run() override;


signals:
    void StopThread();

public slots:
    void stop();

private:
    void msleep(int ms);

private:
    bool _stop;

    std::vector<float> &_x;
    std::vector<float> &_y;
    int _framerate;
    QPointer<AmSpectrDialog> _AS_dialog;
};

#endif
