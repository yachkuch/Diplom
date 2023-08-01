#include "widgethelper.h"

WidgetHelper::WidgetHelper(QWidget *parent) : QWidget(parent)
{

}

void *WidgetHelper::makeFrame(QFrame *widg , QLayout *frame_l)
{
    widg->setFrameStyle(QFrame::Box);
    widg->setLayout(frame_l);
}

QList<QPointF> WidgetHelper::makeList(QMap<int, QPointF> points)
{
    QList<QPointF> list;
    QMapIterator <int,QPointF> iterator(points);
    while(iterator.hasNext()){
        iterator.next();
        list.append(iterator.value());
    }
    return list;
}

float WidgetHelper::calculatemiddleValue(QList<float> values)
{
    float value = 0;
    int schetch = 0;
    QListIterator <float> iter(values);
    while (iter.hasNext()) {
        value = value+iter.next();
        schetch++;
    }
    return value/schetch;
}

