#include "QCustomPlot/DataPlotter.h"
#include "ui/AmSpectrDialog.h"
#include "ui_amspectrdialog.h"

// for debug purposes
#include <iostream>

DataPlotter::DataPlotter(AmSpectrDialog *plotting_canvas, std::vector<float> &x, std::vector<float> &y, std::vector<float> &yHor, std::vector<float> &yVer, int framerate, QObject *parent) :
    QObject(parent),
    _x { x },
    _y { y },
    _yHor { yHor },
    _yVer { yVer },
    _framerate{ framerate },
    _plottingCanvas { plotting_canvas }
{
    _stop = false;
}

DataPlotter::~DataPlotter()
{
    std::cout<<"DP DESTRUCT!"<<std::endl;

}

void DataPlotter::ExecutePlotting()
{
    // TODO: keep DRY! Refactor it later!
    while (!_stop)
    {
        std::cout<<"Executing plotting"<<std::endl;
        // TODO: make it more efficient (right now there are a lot of copying and etc.)
        // Transform std::vector to QVector
        QVector<double> x(qAsConst(_x).size());
        std::copy(_x.begin(), _x.end(), x.begin());

        // Common magnitudes
        QVector<double> y(qAsConst(_y).size());
        std::copy(_y.begin(), _y.end(), y.begin());
        _plottingCanvas->ui->plot->graph()->setData(x, y);
        _plottingCanvas->ui->plot->replot();

        // Horizontal magnitudes
        QVector<double> yHor(qAsConst(_yHor).size());
        std::copy(_yHor.begin(), _yHor.end(), yHor.begin());
        _plottingCanvas->ui->plotHor->graph()->setData(x, yHor);
        _plottingCanvas->ui->plotHor->replot();

        // Vertical magnitudes
        QVector<double> yVer(qAsConst(_yVer).size());
        std::copy(_yVer.begin(), _yVer.end(), yVer.begin());
        _plottingCanvas->ui->plotVer->graph()->setData(x, yVer);
        _plottingCanvas->ui->plotVer->replot();

        int delay = (LIVE_CALC_REFRESH_RATIO*1000/_framerate);

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
