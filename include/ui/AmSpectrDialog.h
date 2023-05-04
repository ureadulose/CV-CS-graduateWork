#ifndef AMSPECTRDIALOG_H
#define AMSPECTRDIALOG_H

#include <QDialog>
#include "QCustomPlot/qcustomplot.h"
#include "opencv2/core.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class AmSpectrDialog; }
QT_END_NAMESPACE

class AmSpectrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AmSpectrDialog(QWidget *parent = nullptr);
    ~AmSpectrDialog();

    void PlotData(std::vector<cv::Point2f> points_to_be_plotted);

private:
    Ui::AmSpectrDialog *ui;
};

#endif // AMSPECTRDIALOG_H
