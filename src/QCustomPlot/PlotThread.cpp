#include "QCustomPlot/PlotThread.h"

// for debug purposes
#include <iostream>

PlotThread::PlotThread(std::vector<float> &x, std::vector<float> &y, int framerate, QObject *parent) :
    QThread(parent),
    _stop{ true },
    _x{ x },
    _y{ y },
    _framerate{ framerate }
{
    _AS_dialog = new AmSpectrDialog(_framerate);
    _AS_dialog->setAttribute(Qt::WA_DeleteOnClose, true);

    connect(_AS_dialog, SIGNAL(ToBeClosed()),
            this, SLOT(stop()));
}

void PlotThread::ShowDialog()
{
    _AS_dialog->show();
    _stop = false;
}

void PlotThread::run()
{
    int delay = (1000/_framerate);
    std::cout<<"run"<<std::endl;
    while (!_stop)
    {
        // plot data
        std::cout<<"plotting data"<<std::endl;
        if (_AS_dialog != nullptr)
            _AS_dialog->PlotData(_x, _y);
        msleep(303);
    }
}

void PlotThread::stop()
{
    _stop = true;
    emit StopThread();
    std::cout<<"emitting stop thread stopped"<<std::endl;
}

void PlotThread::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
