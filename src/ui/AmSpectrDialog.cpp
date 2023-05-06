#include "ui/AmSpectrDialog.h"
#include "ui_amspectrdialog.h"

// for debug purposes
#include <iostream>

AmSpectrDialog::AmSpectrDialog(int framerate, QWidget *parent) :
    QDialog(parent),
//    _x { x },
//    _y { y },
    _framerate{ framerate },
    ui(new Ui::AmSpectrDialog)
{
    ui->setupUi(this);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot->legend->setVisible(false);
    ui->plot->yAxis->setLabel("");
    ui->plot->xAxis->setLabel("Frequency");
    ui->plot->xAxis->setRange(0.0, (double)(framerate) / 2.0);
    ui->plot->yAxis->setRange(0.0, 1.0);
    ui->plot->replot();
    ui->plot->clearGraphs();
    ui->plot->addGraph();

    ui->plot->graph()->setPen(QPen(Qt::black));
}

AmSpectrDialog::~AmSpectrDialog()
{
    std::cout<<"amspectrdialog destructor"<<std::endl;
    delete ui;
}

void AmSpectrDialog::PlotData(std::vector<float> &_x, std::vector<float> &_y)
{
    // Преобразуем векторы в QVector
    QVector<double> x(qAsConst(_x).size());
    std::copy(_x.begin(), _x.end(), x.begin());
    QVector<double> y(qAsConst(_y).size());
    std::copy(_y.begin(), _y.end(), y.begin());
    ui->plot->graph()->setData(x, y);
    ui->plot->replot();
}

void AmSpectrDialog::closeEvent(QCloseEvent *ev)
{
    emit ToBeClosed();
}
