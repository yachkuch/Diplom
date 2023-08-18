#include "database.h"
#include <QDebug>
#include "logger.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
}

QMap<int, QPointF> DataBase::getPointsOmega()
{
    return PointsMapOmega;
}

QMap <int, QPointF> DataBase::getPointsUSRP()
{
    return PointsMapUsrp;
}

QPair<QPointF, QPointF> DataBase::getLeftDownPoint()
{
    return qMakePair(LeftdownPoint,RightTopPoint);
}

QPair<int, int> DataBase::getXLimites()
{
    return XLimits;
}

QPair<int, int> DataBase::getYLimites()
{
    return YLimitss;
}
void DataBase::write_points_from_file(QMap<int, QPointF> USRP, QMap<int, QPointF> Omega)
{
    QFile file(QDir::currentPath()+"./base.txt");
    if(file.open(QIODevice::WriteOnly | QFile::Append | QFile::Text)){
        qDebug(logInfo())<<"Пара изображений проанализирована, дописываем точки";
        QTextStream strem(&file);
        strem<<&NameForWritingFromFile<<"\n";
        strem<<"USPR \n";
        QMapIterator<int,QPointF> iter(USRP);
        while (iter.hasNext()) {
            iter.next();
            strem<<iter.value().x()<<" "<<iter.value().y()<<" \n";
        }
        strem<<"OMEGA \n";
        QMapIterator<int,QPointF> iter2(Omega);
        while (iter2.hasNext()) {
            iter2.next();
            strem<<iter2.value().x()<<" "<<iter2.value().y()<<" \n";
        }
        file.close();
    } else {
       // QMessageBox mb;
       // mb.setText("Файл для записи данных графиков не был открыт");
       // qDebug(logWarning())<<"Файл для записи данных графиков не был открыт";
       // mb.exec();
    }
}

QString DataBase::getNameForWritingFromFile() const
{
    return NameForWritingFromFile;
}

void DataBase::setNameForWritingFromFile(const QString &newNameForWritingFromFile)
{
    NameForWritingFromFile = newNameForWritingFromFile;
}

QPointF DataBase::Middle(QList<QPointF> points)
{
    QPointF result;
    QListIterator<QPointF> iter(points);
    while (iter.hasNext()) {
        QPointF value = iter.next();
        result.setX(result.x() + value.x());
        result.setY(result.y() + value.y());
    }
    result.setX(result.x()/points.size());
    result.setY(result.y()/points.size());

    return result;
}

void DataBase::setInformation(QPointF LeftdownPoint, QPointF RightTopPoint, QPair<int, int> XLimits, QPair<int,int> YLimits , QMultiMap<int, QPointF> Points, int TypeScenary)
{
    this->XLimits = XLimits;
    this->YLimitss = YLimits;
    this->RightTopPoint = RightTopPoint;
    this->LeftdownPoint = LeftdownPoint;
    double sizeFromPixelX = abs( static_cast<double>((RightTopPoint.x()-LeftdownPoint.x())));
    double sizeFromPixelY = abs( static_cast<double>((RightTopPoint.y()-LeftdownPoint.y())));
    double SizeOfScaleX = abs(XLimits.first - XLimits.second);
    double SizeOfScaleY = abs(YLimits.first - YLimits.second);
    double koeffX = SizeOfScaleX/sizeFromPixelX; //! ?Получаем коэффицент показывающей сколько пикселей в одной единице шкалы
    double koeffY = SizeOfScaleY/sizeFromPixelY;
    QMap <int, int> iskluchen;
    if(Points.isEmpty() == false){
        QMultiMapIterator <int,QPointF> iter(Points);
        while (iter.hasNext()) {
            iter.next();
            if(!iskluchen.contains(iter.key())){
                QPointF midPoint;
                QList <QPointF> middingPoints = Points.values(iter.key());
                iskluchen.insert(iter.key(),iter.key());
                if(Points.size()>1){
                    midPoint = Middle(middingPoints);
                } else{
                    midPoint = middingPoints.first();
                }
                // протестировать как происходит рассчет и добавить что если точек всего одна или нет вообще вызова не происходит
                QPointF Value(abs(koeffX*(midPoint.x()-LeftdownPoint.x())+XLimits.first),/*abs*/(-koeffY*(midPoint.y() - RightTopPoint.y()) + YLimits.second /*+ LeftdownPoint.y()*/));
                if(TypeScenary==1){
                    PointsMapUsrp.insert(iter.key(),Value);
                } else if (TypeScenary == 2){
                    PointsMapOmega.insert(iter.key(),Value);
                }
            }
        }
    }
    else {
        QMessageBox MB;
        MB.setText("[ DataBase::setInformation ] набор точек пришел пустой");
    }
}

void DataBase::ClearDatabase()
{
        this->PointsMapUsrp.clear();
        this->PointsMapOmega.clear();
}
