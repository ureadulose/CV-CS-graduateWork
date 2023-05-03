#include "ui/AmSpectrDialog.h"
#include "ui_amspectrdialog.h"

AmSpectrDialog::AmSpectrDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AmSpectrDialog)
{
    ui->setupUi(this);
}

AmSpectrDialog::~AmSpectrDialog()
{
    delete ui;
}

void AmSpectrDialog::PlotData(std::vector<cv::Point2f> points_to_be_plotted)
{

    //QBarSeries *series = new QBarSeries();
}
