#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageWindow; }
QT_END_NAMESPACE

class ImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    ImageWindow(QWidget *parent = nullptr);
    ~ImageWindow();

private:
    Ui::ImageWindow *ui;
};
#endif // IMAGEWINDOW_H
