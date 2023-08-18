#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVector>

class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);

    QMap<int,QPointF> getPointsOmega();
    QMap<int,QPointF> getPointsUSRP();
    QPair<QPointF,QPointF> getLeftDownPoint();
    QPair<int,int> getXLimites();
    QPair<int,int> getYLimites();

    void write_points_from_file(QMap<int,QPointF> USRP,QMap<int,QPointF> OMega);

    QString getNameForWritingFromFile() const;
    void setNameForWritingFromFile(const QString &newNameForWritingFromFile);

private:

    QMap<int,QPointF> PointsMapUsrp;
    QMap<int,QPointF> PointsMapOmega;
    QPointF LeftdownPoint;
    QPointF RightTopPoint;
    QPair<int, int> XLimits;
    QPair<int,int> YLimitss;

    QString NameForWritingFromFile;

    /****************Функции***************/
    /**
     * @brief Middle Усредняет значение по набору точек, необходима в том случае, если на одной
     * линии оси у встречается сразу несколько точек
     * @param points Набор точек которые необходимо усренить
     * @return Среднее значение точки
     */
    QPointF Middle(QList<QPointF> points);

signals:

public slots:
    /**
     * @brief setInformation Перещет полученного набора точек
     * @param LeftdownPoint Левая нижняя точка на координатной оси
     * @param RightTopPoint Правая верхняя точка на координатной оси
     * @param XLimits Пределы в которых анализируется ось Х на графике
     * @param YLimitss Пределы в которых анализируется ось У на графике
     * @param Points Набор точек которые необходимо проанализировать и переситать
     * @param TypeSceny идентификатор в какой из наборов точек необходимо записывать полученные график с 1 форматом jpg и это usrp , если параметр 2 то это формат
         * bmp и это снимала omega
     */
    void setInformation( QPointF LeftdownPoint, QPointF RightTopPoint, QPair<int, int> XLimits, QPair<int,int> YLimitss , QMultiMap<int,QPointF> Points, int TypeScenary);
    /**
     * @brief ClearDatabase Полная очистка базы данных
     */
    void ClearDatabase();
};

#endif // DATABASE_H
