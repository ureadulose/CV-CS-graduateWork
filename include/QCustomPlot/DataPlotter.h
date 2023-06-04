#ifndef PLOT_THREAD_H
#define PLOT_THREAD_H

#include <QObject>

// apparently QCustomPlot can't handle high fps on PCs with low performance (which probably isn't really needed cause it's just a plot)
// but anyway i had runtime errors even when it refreshes with 30 fps, change plot later
const int LIVE_CALC_REFRESH_RATIO = 8;

class AmSpectrDialog;

class DataPlotter : public QObject
{
    Q_OBJECT

public:
    explicit DataPlotter(AmSpectrDialog *plotting_canvas, std::vector<float> &x, std::vector<float> &y, std::vector<float> &yHor, std::vector<float> &yVer, int framerate, QObject *parent = nullptr);
    ~DataPlotter();

    void StopPlotting();

public slots:
    void ExecutePlotting();

private:
    void msleep(int ms);

private:
    bool _stop;

    std::vector<float> &_x;
    std::vector<float> &_y;
    std::vector<float> &_yHor;
    std::vector<float> &_yVer;
    int _framerate;

    AmSpectrDialog *_plottingCanvas;

};

#endif
