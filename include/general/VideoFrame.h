#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>



class VideoFrame : public QLabel
{
    Q_OBJECT

public:
    explicit VideoFrame(QWidget *parent = 0);
    //~VideoFrame();

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

    QPointF GetCurrentMousePos();


private:
    QPointF _curr_mouse_pos;

signals:
    void MousePressedSignal();
    void MousePosSignal();
    void MouseLeftFrameSignal();

private slots:

};

#endif // EVENT_HANDLER_H
