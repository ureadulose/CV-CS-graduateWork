#include "QCustomPlot/DataPlotter.h"

#include "ui/AmSpectrDialog.h"
#include "ui_amspectrdialog.h"

// for debug purposes
#include <iostream>


// TODO: Make dynamical amount of plots in AmSpectrDialog!

DataPlotter::DataPlotter(AmSpectrDialog *plottingCanvas, std::vector<float> &x, std::vector<QPointF> &y, int framerate, QObject *parent) :
    QObject(parent),
    _x { x },
    _y { y },
    _framerate{ framerate },
    _plottingCanvas { plottingCanvas }
{
    _stop = false;
    for (int i = 0; i < CURVES_AMOUNT; i++)
    {
        _curves[i] = new QwtPlotCurve();
    }

    QLayout* layout =_plottingCanvas->layout();

    for (int i = 0; i < layout->count(); i++)
    {
        _plots[i] = qobject_cast<QwtPlot*>(layout->itemAt(i)->widget());
    }
}

DataPlotter::~DataPlotter()
{
    for (int i = 0; i < CURVES_AMOUNT; i++)
    {
        delete _curves[i];
    }
    std::cout<<"DP DESTRUCT!"<<std::endl;
}

void DataPlotter::ExecutePlotting()
{
    // TODO: keep DRY! Refactor it later!
    while (!_stop)
    {
        std::cout<<"Executing plotting"<<std::endl;

        QVector<float> x;
        QVector<float> y;
        QVector<float> yHor;
        QVector<float> yVer;

        QVector<float>* Ys[3];
        Ys[0] = &y;
        Ys[1] = &yHor;
        Ys[2] = &yVer;

        for (size_t i = 0; i < _x.size(); i++)
        {
            x.push_back(_x[i]);
            y.push_back(_y[i].x() * _y[i].x() + _y[i].y() * _y[i].y());
            yHor.push_back(_y[i].x());
            yVer.push_back(_y[i].y());
        }

        for (int i = 0; i < CURVES_AMOUNT; i++)
        {
            PlotData(_curves[i], _plots[i], x, *Ys[i]);
        }


        int delay = (LIVE_CALC_REFRESH_RATIO*1000/_framerate);

        this->msleep(delay);
    }
    std::cout<<"Stopped plotting"<<std::endl;
}

void DataPlotter::PlotData(QwtPlotCurve *curve, QwtPlot *plot, const QVector<float> &x, const QVector<float> &y)
{
    curve->setSamples(x.data(), y.data(), x.size());
    curve->attach(plot);
    plot->replot();
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
