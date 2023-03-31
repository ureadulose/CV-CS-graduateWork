#include "general/VideoFrame.h"

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
    emit MousePressedSignal();
}

void VideoFrame::leaveEvent(QEvent *)
{
    emit MouseLeftFrameSignal();
}

QPointF VideoFrame::GetCurrentMousePos()
{
    return _curr_mouse_pos;
}
