#include "ui/AmSpectrDialog.h"
#include "ui_amspectrdialog.h"

// for debug purposes
#include <iostream>
#include <QDebug>

AmSpectrDialog::AmSpectrDialog(std::vector<float> &x, std::vector<QPointF> &y, int framerate, float maxVal, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AmSpectrDialog),
    _stop { false },
    _x { x },
    _y { y },
    _framerate{ framerate }
{
    // TODO: refactor! It's not DRY!
    ui->setupUi(this);
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
    _dataPlotter = new DataPlotter(this, _x, _y, _framerate);
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
