#include "ui/mainwindow.h"
#include <opencv2/core.hpp>
#include <QApplication>
#include <iostream>
#include "general/TrackerBody.h"

int main(int argc, char *argv[])
{
//    cv::Mat frame;
//    std::cout<<"ass"<<std::endl;
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
    std::string filename = "C:/Users/ass/source/repos/CV-CS-graduateWork/resources/1.mp4";
    std::string window_name = "my Window";
    TrackerBody TB(filename, window_name);
    TB.Run();
}
