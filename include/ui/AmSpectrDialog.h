#ifndef AMSPECTRDIALOG_H
#define AMSPECTRDIALOG_H

#include <QDialog>
#include <QThread>

#include "QCustomPlot/qcustomplot.h"
#include "QCustomPlot/DataPlotter.h"

#include "opencv2/core.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class AmSpectrDialog;
}
QT_END_NAMESPACE

class AmSpectrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AmSpectrDialog(std::vector<float> &x, std::vector<float> &y, int framerate, QWidget *parent = nullptr);
    ~AmSpectrDialog();

    void Startup();

    Ui::AmSpectrDialog *ui;

signals:
    void finished();

private slots:
    void closeEvent(QCloseEvent *ev);

private:
    void msleep(int ms);

private:
    QThread *_plotThread;
    DataPlotter *_dataPlotter;

    bool _stop;
    std::vector<float> &_x;
    std::vector<float> &_y;
    int _framerate;
};

#endif // AMSPECTRDIALOG_H
