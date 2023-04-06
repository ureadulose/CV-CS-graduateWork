#include "ui/ProcessingWindow.h"
#include <opencv2/core.hpp>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
//    cv::Mat frame;
    std::cout << "ass3es" << std::endl;
    QApplication a(argc, argv);
    ProcessingWindow *w = new ProcessingWindow();
    w->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
    return a.exec();
//    std::string filename = "C:/Users/ass/source/repos/CV-CS-graduateWork/resources/1.mp4";
//    std::string window_name = "my Window";
//    TrackerBody TB(filename, window_name);
//    return TB.Run();
}
