#ifndef AMSPECTRDIALOG_H
#define AMSPECTRDIALOG_H

#include <QDialog>
#include <QVector>

#include "QCustomPlot/qcustomplot.h"
#include "opencv2/core.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class AmSpectrDialog; }
QT_END_NAMESPACE

class AmSpectrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AmSpectrDialog(int framerate, QWidget *parent = nullptr);
    ~AmSpectrDialog();

    void PlotData(std::vector<float> &_x, std::vector<float> &_y);

signals:
    void ToBeClosed();

private slots:
    void closeEvent(QCloseEvent *ev);

private:
    int _framerate;
    Ui::AmSpectrDialog *ui;
};

#endif // AMSPECTRDIALOG_H
