#include "ui/ProcessingWindow.h"
//#include "ui/ImageWindow.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <QApplication>
#include <iostream>
#include <QFile>

int main(int argc, char *argv[])
{
//    cv::Mat frame;AmSpectrDialog ImageWindow
    std::cout << "ass3es" << std::endl;
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;
    bool haveOpenCL = cv::ocl::haveOpenCL();

    if (haveOpenCL) {
        std::cout << "OpenCL is supported" << std::endl;
    } else {
        std::cout << "OpenCL is not supported" << std::endl;
    }
    QApplication app(argc, argv);

//    ImageWindow *w = new ImageWindow();
    ProcessingWindow *w = new ProcessingWindow();
    w->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
    return app.exec();
}
