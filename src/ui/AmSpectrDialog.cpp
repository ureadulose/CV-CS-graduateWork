#include "ui/AmSpectrDialog.h"
#include "ui_amspectrdialog.h"

AmSpectrDialog::AmSpectrDialog(QWidget *parent) :
    QDialog(parent),
//    _x { x },
//    _y { y },
    ui(new Ui::AmSpectrDialog)
{
    ui->setupUi(this);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

AmSpectrDialog::~AmSpectrDialog()
{
    delete ui;
}

void AmSpectrDialog::PlotData(std::vector<cv::Point2f> points_to_be_plotted)
{

    //QBarSeries *series = new QBarSeries();
}

void AmSpectrDialog::closeEvent(QCloseEvent *ev)
{
    emit ToBeClosed();
}
