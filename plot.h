#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QGraphicsScene>
#include <QString>
#include <QObject>

#include "database.h"
#include "widgethelper.h"

namespace Ui {
class Plot;
}

class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(DataBase *DB,QWidget *parent = nullptr);
    ~Plot();

    /**
     * @brief setDirforSave Записывает, куда необходимо сохранить полученные графики
     * @param Dir Путь до места сохранения
     */
    void setDirforSave(QString Dir);

private:
    Ui::Plot *ui;

    DataBase *DataBase;
    QWidget *parent;

    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsScene *scene4;

    /**
     * @brief LimitsXY Пара пределов по х и у для разностного графика
     */
    QPair<QPair<float,float>,QPair<float,float>> LimitsDiffXY;
    QPair<QPair<float,float>,QPair<float,float>> LimitsCorrelationXY;

    float NormalizeValueCorrelation = 0;

    //! График спектра считанного с фотографии
    QChart *ChartOmega;
    QChart *ChartUSRP;
    //! График после результатов вычислений
    QChart *ChartDiff;
    QChart *ChartCorellation;
    //! Путь для сохранения скриншотов
    QString SavePath;
    //! Имя сохраняемого скриншота
    QString NameImage;

    QMap<int,QPointF> MapUSRP;
    QMap<int,QPointF> MapOmega;
    QList <QPointF> ListUSRP;
    QList <QPointF> ListOmega;
    QList<QPointF> listDiff;
    QList<QPointF> listCorrel;


    /*****************Функции************************/

    /**
     * @brief LinesAppend Заполняет список серии для графика из базв
     * @param points мап точек из базы
     * @return список для серии
     */
    QList<QPointF> LinesAppend(QMap<int,QPointF> points);
    /**
     * @brief CalculatePlotdiff рассчет разностного графика (разность из омеги вычитается USRP)
     * @param PointsOmega набор точек омеги
     * @param PointsUSRP набор точек USRP
     * @return точки разностного графика
     */
    QList<QPointF> CalculatePlotdiff(QMap<int,QPointF> PointsOmega , QMap<int,QPointF> PointsUSRP);
    /**
     * @brief MakingMiddle Проводит усреднения значения в мультимапе
     * @param points набор точек, которые будут усредняться
     * @return мап усредненных значений
     */
    QMap<int,QPointF> MakingMiddle(QMultiMap<int,QPointF> points);
    /**
     * @brief calculateLimits ищет пределы для выставления на графике
     * @param points набор точек в котором ощутся пределы
     * @return первая пара мин мах по х вторая пара мин макс по у
     */
    QPair<QPair<float,float>,QPair<float,float>> calculateLimits(QList<QPointF> points );
    QList<QPointF> calculateSvertka(QList<QPointF> firstfunction, QList<QPointF> secondfunction);
    float calculateKoeffCorellation(QList<QPointF> firstfunction, QList<QPointF> secondfunction);

private slots:

    /**
     * @brief MakeScreen Делает скриншот изображения
     * @param Виджет который необходимо заскринисть
     */
    void MakeScreen(QWidget *widg);
    /**
     * @brief BufFunctByMakeScreen Промежуточный слот для того, чтоб сделать скриншот
     */
    void BufFunctByMakeScreen();
public slots:
    /**
     * @brief MakePlot Функция строит график
     */
    void MakePlot();

};

#endif // PLOT_H
