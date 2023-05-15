#include "VideoHandling/VideoFrame.h"

VideoFrame::VideoFrame(QWidget *parent) :
    QLabel(parent)
{
}

VideoFrame::~VideoFrame()
{
}

void VideoFrame::mouseMoveEvent(QMouseEvent *ev)
{
    this->_curr_mouse_pos = ev->position();
    emit MousePosSignal();
}

void VideoFrame::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit MouseLeftButtonPressedSignal(EventType::MouseLeftPressed);
    else if (ev->button() == Qt::RightButton)
        emit MouseRightButtonPressedSignal(EventType::MouseRightPressed);
}

void VideoFrame::leaveEvent(QEvent *)
{
    emit MouseLeftFrameSignal();
}

QPointF VideoFrame::GetCurrentMousePos()
{
    return _curr_mouse_pos;
}
