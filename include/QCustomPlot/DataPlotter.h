#ifndef PLOT_THREAD_H
#define PLOT_THREAD_H

#include "qwt_plot_curve.h"
#include <QObject>

// apparently QCustomPlot can't handle high fps on PCs with low performance (which probably isn't really needed cause it's just a plot)
// but anyway i had runtime errors even when it refreshes with 30 fps, change plot later
const int LIVE_CALC_REFRESH_RATIO = 8;
const int CURVES_AMOUNT = 3;

class AmSpectrDialog;

class DataPlotter : public QObject
{
    Q_OBJECT

public:
    explicit DataPlotter(AmSpectrDialog *plottingCanvas, std::vector<float> &x, std::vector<QPointF> &y, int framerate, QObject *parent = nullptr);
    ~DataPlotter();

    void StopPlotting();

public slots:
    void ExecutePlotting();

private:
    void PlotData(QwtPlotCurve *curve, QwtPlot *plot, const QVector<float> &x, const QVector<float> &y);
    void msleep(int ms);

private:
    bool _stop;
    QwtPlotCurve *_curves[3];
    QwtPlot *_plots[3];

    std::vector<float> &_x;
    std::vector<QPointF> &_y;
    int _framerate;

    AmSpectrDialog *_plottingCanvas;

};

#endif
