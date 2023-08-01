#ifndef WIDGETHELPER_H
#define WIDGETHELPER_H

#include <QWidget>
#include <QFrame>
#include <QLayout>
#include <QMap>
#include <QList>

class WidgetHelper : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetHelper(QWidget *parent = nullptr);

    static void* makeFrame(QFrame *widg, QLayout *frame_l);
    static QList<QPointF> makeList(QMap<int,QPointF> points);
    static float calculatemiddleValue(QList<float> values);

signals:

};

#endif // WIDGETHELPER_H
