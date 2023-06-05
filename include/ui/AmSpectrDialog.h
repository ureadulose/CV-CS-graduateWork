#ifndef AMSPECTRDIALOG_H
#define AMSPECTRDIALOG_H

#include <QDialog>
#include <QThread>

#include "QCustomPlot/DataPlotter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AmSpectrDialog;
}
QT_END_NAMESPACE

class AmSpectrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AmSpectrDialog(std::vector<float> &x, std::vector<QPointF> &y, int framerate, float maxVal = 0.01f, QWidget *parent = nullptr);
    ~AmSpectrDialog();

    void SetupThread();

    // TODO: make it safe
    Ui::AmSpectrDialog *ui;

signals:
    // i know it is an overload (QDialog::finished()) but i cant think of a better name so probably rename it later
    void finished();

private slots:
    void closeEvent(QCloseEvent *ev);

private:
    void msleep(int ms);
    void StopThreadAndFinish();

private:
    QThread *_plotThread;
    DataPlotter *_dataPlotter;

    bool _stop;
    std::vector<float> &_x;
    std::vector<QPointF> &_y;
    int _framerate;
};

#endif // AMSPECTRDIALOG_H
