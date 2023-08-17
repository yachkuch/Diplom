#include "scroll.h"

SCroll::SCroll(QWidget *parent)
{
    this->parent = parent;

    connect(this, SIGNAL(coordinates(QPointF)), parent, SLOT(gettingCoordFromScroll(QPointF)));
}

void SCroll::mouseDoubleClickEvent(QMouseEvent *mouse)
{
    emit(coordinates(mouse->localPos()));
    //qDebug()<<horizontalScrollBar()->value();
    //qDebug()<<mouse->localPos();
}

void SCroll::wheelEvent(QWheelEvent *ev)
{ //qDebug()<<"work"<<ev->angleDelta();
    if (ev->angleDelta().y()>0){
        //qDebug()<<"+";


    } else if (ev->angleDelta().y()<0){
        //qDebug()<<"-";
    }
}
