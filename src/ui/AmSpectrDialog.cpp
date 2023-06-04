#include "ui/AmSpectrDialog.h"
#include "ui_amspectrdialog.h"

// for debug purposes
#include <iostream>
#include <QDebug>

AmSpectrDialog::AmSpectrDialog(std::vector<float> &x, std::vector<float> &y, std::vector<float> &yHor, std::vector<float> &yVer, int framerate, float maxVal, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AmSpectrDialog),
    _stop { false },
    _x { x },
    _y { y },
    _yHor { yHor },
    _yVer { yVer },
    _framerate{ framerate }
{
    // TODO: refactor! It's not DRY!
    ui->setupUi(this);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot->legend->setVisible(false);
    ui->plot->yAxis->setLabel("");
    ui->plot->xAxis->setLabel("Frequency");
    ui->plot->xAxis->setRange(0.0, (double)(framerate) / 2.0);
    ui->plot->yAxis->setRange(0.0, (double)(maxVal));
    ui->plot->replot();
    ui->plot->clearGraphs();
    ui->plot->addGraph();

    ui->plot->graph()->setPen(QPen(Qt::black));

    // Horizontal
    ui->plotHor->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plotHor->legend->setVisible(false);
    ui->plotHor->yAxis->setLabel("");
    ui->plotHor->xAxis->setLabel("Frequency in horizontal axis");
    ui->plotHor->xAxis->setRange(0.0, (double)(framerate) / 2.0);
    ui->plotHor->yAxis->setRange(0.0, (double)(maxVal));
    ui->plotHor->replot();
    ui->plotHor->clearGraphs();
    ui->plotHor->addGraph();

    ui->plotHor->graph()->setPen(QPen(Qt::black));

    // Vertical
    ui->plotVer->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plotVer->legend->setVisible(false);
    ui->plotVer->yAxis->setLabel("");
    ui->plotVer->xAxis->setLabel("Frequency in vertical axis");
    ui->plotVer->xAxis->setRange(0.0, (double)(framerate) / 2.0);
    ui->plotVer->yAxis->setRange(0.0, (double)(maxVal));
    ui->plotVer->replot();
    ui->plotVer->clearGraphs();
    ui->plotVer->addGraph();

    ui->plotVer->graph()->setPen(QPen(Qt::black));
}

AmSpectrDialog::~AmSpectrDialog()
{
    StopThreadAndFinish();
//    hide();
    std::cout<<"ASD DESTRUCT!"<<std::endl;
    delete _dataPlotter;
    delete _plotThread;
    delete ui;
}

void AmSpectrDialog::SetupThread()
{
    _plotThread = new QThread();
    // TODO: it's probably more clear to send actual delay and not framerate directly
    _dataPlotter = new DataPlotter(this, _x, _y, _yHor, _yVer, _framerate);
    _dataPlotter->moveToThread(_plotThread);
    connect(_plotThread, SIGNAL(started()), _dataPlotter, SLOT(ExecutePlotting()));

    _plotThread->start();

}

void AmSpectrDialog::closeEvent(QCloseEvent *ev)
{
    emit finished();
}

void AmSpectrDialog::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);

}

void AmSpectrDialog::StopThreadAndFinish()
{
    _dataPlotter->StopPlotting();

    _plotThread->quit();

    if (_plotThread->isRunning())
    {
        _plotThread->wait();
    }
}
