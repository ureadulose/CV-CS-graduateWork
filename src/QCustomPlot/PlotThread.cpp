#include "QCustomPlot/PlotThread.h"

// for debug purposes
#include <iostream>

PlotThread::PlotThread(int framerate, QObject *parent) :
    QThread(parent),
    _framerate{ framerate }
{
    _AS_dialog = new AmSpectrDialog();
    _AS_dialog->setAttribute(Qt::WA_DeleteOnClose, true);

    connect(_AS_dialog, SIGNAL(ToBeClosed()),
            this, SLOT(stop()));
}

void PlotThread::run()
{
    _AS_dialog->show();
    int delay = (1000/_framerate);

    while (!isInterruptionRequested())
    {
        // plot data
        std::cout<<"plotting data"<<std::endl;
        msleep(303);
    }
}

void PlotThread::stop()
{
    emit StopThread();
    std::cout<<"emitting stop thread stopped"<<std::endl;
}

void PlotThread::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
