QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= app_bundle

SOURCES +=  \
    src/CvFrameBufferHandler.cpp \
    src/ImageWindow.cpp \
    src/PointTracker.cpp \
    src/VideoFrame.cpp \
    src/VideoTrackerPlayer.cpp \
    src/main.cpp

INCLUDEPATH += $$PWD \
    include

HEADERS += \
    include/general/CvFrameBufferHandler.h \
    include/general/PointTracker.h \
    include/general/VideoFrame.h \
    include/general/VideoTrackerPlayer.h \
    include/ui/ImageWindow.h

FORMS += \
    ui/mainwindow.ui

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
