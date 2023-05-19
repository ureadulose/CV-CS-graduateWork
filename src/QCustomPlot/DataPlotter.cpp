#include "QCustomPlot/DataPlotter.h"
#include "ui/AmSpectrDialog.h"
#include "ui_amspectrdialog.h"

// for debug purposes
#include <iostream>

DataPlotter::DataPlotter(AmSpectrDialog *plotting_canvas, std::vector<float> &x, std::vector<float> &y, int framerate, QObject *parent) :
    QObject(parent),
    _x { x },
    _y { y },
    _framerate{ framerate },
    _plotting_canvas { plotting_canvas }
{
    _stop = false;
}

DataPlotter::~DataPlotter()
{
    std::cout<<"DP DESTRUCT!"<<std::endl;

}

void DataPlotter::ExecutePlotting()
{
    while (!_stop)
    {
        std::cout<<"Executing plotting"<<std::endl;
        // TODO: make it more efficient (right now there are a lot of copying and etc.)
        // Transform std::vector to QVector
        QVector<double> x(qAsConst(_x).size());
        std::copy(_x.begin(), _x.end(), x.begin());
        QVector<double> y(qAsConst(_y).size());
        std::copy(_y.begin(), _y.end(), y.begin());
        _plotting_canvas->ui->plot->graph()->setData(x, y);
        _plotting_canvas->ui->plot->replot();

        int delay = (1000/_framerate);
        this->msleep(delay);
    }
    std::cout<<"Stopped plotting"<<std::endl;
}

void DataPlotter::StopPlotting()
{
    _stop = true;
}
void DataPlotter::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
