#ifndef PLOT_THREAD_H
#define PLOT_THREAD_H

#include <QObject>

class AmSpectrDialog;

class DataPlotter : public QObject
{
    Q_OBJECT

public:
    explicit DataPlotter(AmSpectrDialog *plotting_canvas, std::vector<float> &x, std::vector<float> &y, int framerate, QObject *parent = nullptr);
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
    int _framerate;

    AmSpectrDialog *_plottingCanvas;

};

#endif
