#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>

#include "MyEnums.h"

class VideoFrame : public QLabel
{
    Q_OBJECT

public:
    explicit VideoFrame(QWidget *parent = 0);
    ~VideoFrame();

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

    QPointF GetCurrentMousePos();


private:
    QPointF _currMousePos;

signals:
    void MouseLeftButtonPressedSignal(EventType event);
    void MouseRightButtonPressedSignal(EventType event);
    void MousePosSignal();
    void MouseLeftFrameSignal();

private slots:

};

#endif // EVENT_HANDLER_H
