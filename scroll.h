#ifndef SCROLL_H
#define SCROLL_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QMouseEvent>
#include <QDebug>
#include <QScrollBar>

class SCroll : public QScrollArea
{
    Q_OBJECT
public:
    SCroll(QWidget *parent);

private:

    QMouseEvent *mouse;
    QWheelEvent *ev;


    QWidget *parent;

    void mouseDoubleClickEvent(QMouseEvent *mouse);
    void wheelEvent(QWheelEvent *ev);
signals:

    void coordinates(QPointF);
private slots:
};

#endif // SCROLL_H
