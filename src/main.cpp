#include "ui/ImageWindow.h"
#include <opencv2/core.hpp>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
//    cv::Mat frame;AmSpectrDialog ImageWindow
    std::cout << "ass3es" << std::endl;
    QApplication a(argc, argv);
    ImageWindow *w = new ImageWindow();
    //ProcessingWindow *w = new ProcessingWindow();
    w->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
    return a.exec();
}
