QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= app_bundle

SOURCES +=  \
    src/PointsHandling/DataPoint.cpp \
    src/PointsHandling/PointTracker.cpp \
    src/PointsHandling/PointsManager.cpp \
    src/QCustomPlot/DataPlotter.cpp \
    src/QCustomPlot/qcustomplot.cpp \
    src/VideoHandling/CvFrameBufferHandler.cpp \
    src/VideoHandling/VideoFrame.cpp \
    src/VideoHandling/VideoTrackerPlayer.cpp \
    src/main.cpp \
    src/ui/AmSpectrDialog.cpp \
    src/ui/ImageWindow.cpp \
    src/ui/ProcessingWindow.cpp

INCLUDEPATH += $$PWD \
    include

HEADERS += \
    include/EventType.h \
    include/PointsHandling/DataPoint.h \
    include/PointsHandling/PointTracker.h \
    include/PointsHandling/PointsManager.h \
    include/QCustomPlot/DataPlotter.h \
    include/QCustomPlot/qcustomplot.h \
    include/VideoHandling/CvFrameBufferHandler.h \
    include/VideoHandling/VideoFrame.h \
    include/VideoHandling/VideoTrackerPlayer.h \
    include/ui/AmSpectrDialog.h \
    include/ui/ImageWindow.h \
    include/ui/ProcessingWindow.h

FORMS += \
    ui/amspectrdialog.ui \
    ui/imagewindow.ui \
    ui/processingwindow.ui

win32: LIBS += -L$$PWD/../../ThirdParty/opencv/opencv470_g/x64/mingw/lib/ -llibopencv_core470.dll -llibopencv_highgui470.dll -llibopencv_imgcodecs470.dll -llibopencv_optflow470.dll -llibopencv_imgproc470.dll -llibopencv_videoio470.dll -llibopencv_tracking470.dll

INCLUDEPATH += $$PWD/../../ThirdParty/opencv/opencv470_g/include
DEPENDPATH += $$PWD/../../ThirdParty/opencv/opencv470_g/include

PRE_TARGETDEPS += $$PWD/../../ThirdParty/opencv/opencv470_g/x64/mingw/lib/libopencv_core470.dll.a
PRE_TARGETDEPS += $$PWD/../../ThirdParty/opencv/opencv470_g/x64/mingw/lib/libopencv_highgui470.dll.a
PRE_TARGETDEPS += $$PWD/../../ThirdParty/opencv/opencv470_g/x64/mingw/lib/libopencv_imgcodecs470.dll.a
PRE_TARGETDEPS += $$PWD/../../ThirdParty/opencv/opencv470_g/x64/mingw/lib/libopencv_optflow470.dll.a
PRE_TARGETDEPS += $$PWD/../../ThirdParty/opencv/opencv470_g/x64/mingw/lib/libopencv_imgproc470.dll.a
PRE_TARGETDEPS += $$PWD/../../ThirdParty/opencv/opencv470_g/x64/mingw/lib/libopencv_videoio470.dll.a
PRE_TARGETDEPS += $$PWD/../../ThirdParty/opencv/opencv470_g/x64/mingw/lib/libopencv_tracking470.dll.a

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
