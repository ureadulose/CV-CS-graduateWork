#ifndef PLOT_THREAD_H
#define PLOT_THREAD_H

#include <QThread>

#include "ui/AmSpectrDialog.h"

class PlotThread : public QThread
{
    Q_OBJECT

public:
    PlotThread(int framerate, QObject *parent = nullptr);

    void run() override;

signals:
    void StopThread();

public slots:
    void stop();

private:
    void msleep(int ms);

private:
    int _framerate;
    AmSpectrDialog *_AS_dialog;
};

#endif
