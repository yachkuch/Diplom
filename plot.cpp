#include "plot.h"
#include "ui_plot.h"

Plot::Plot(class DataBase *DB, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);

    ui->graphicsView_8->hide();

    this->DataBase = DB;
    this->parent = parent;

    scene = new QGraphicsScene;
    scene2 = new QGraphicsScene;
    scene3 = new QGraphicsScene;
    scene4 = new QGraphicsScene;

    ui->graphicsView_5->setScene(scene);
    ui->graphicsView_6->setScene(scene2);
    ui->graphicsView_7->setScene(scene3);
    ui->graphicsView_8->setScene(scene4);

    ChartOmega = new QChart();
    ChartUSRP = new QChart();
    ChartDiff = new QChart();
    ChartCorellation = new QChart();

    scene->addItem(ChartOmega);
    scene2->addItem(ChartUSRP);
    scene3->addItem(ChartDiff);
    scene4->addItem(ChartCorellation);

    connect(ui->pbStart,SIGNAL(pressed()), this, SLOT(MakePlot()));
    connect(ui->pbScreenshot, SIGNAL(pressed()), this , SLOT(BufFunctByMakeScreen()));

    MakePlot();
}

Plot::~Plot()
{
    delete ui;
}

QList<QPointF> Plot::LinesAppend(QMap<int, QPointF> points)
{
    QList<QPointF> ListPoints;
    QMapIterator <int, QPointF> iter(points);
    while (iter.hasNext()) {
        iter.next();
        ListPoints.append(iter.value());
    }
    return ListPoints;
}

QList<QPointF> Plot::CalculatePlotdiff(QMap<int, QPointF> PointsOmega, QMap<int, QPointF> PointsUSRP)
{
    MapOmega.clear();
    MapUSRP.clear();
    ListUSRP.clear();
    ListOmega.clear();
    QMultiMap <int,QPointF> diffPointsUSRP;
    QMultiMap <int,QPointF> diffPointsOmega;
    QList<QPointF> listDiff;
    int step = 10;
    QMapIterator <int,QPointF> iterOmega(PointsOmega);
    while (iterOmega.hasNext()) {
        iterOmega.next();
        int val = iterOmega.value().x();
        val = (int)val/step;
        QPointF value;
        value.setX((int)val*step);
        value.setY(iterOmega.value().y());
        diffPointsOmega.insert((int)val*step,value);
    }
    QMapIterator <int,QPointF> iterUSRP(PointsUSRP);
    while (iterUSRP.hasNext()) {
        iterUSRP.next();
        int val = iterUSRP.value().x();
        val = (int)val/step;
        if(diffPointsOmega.contains((int)val*step)){
            QPointF value;
            value.setX((int)val*step);
            value.setY(iterUSRP.value().y());
            diffPointsUSRP.insert((int)val*step,value);
        }
    }
    QMultiMapIterator<int,QPointF> iterClear(diffPointsOmega);
    while (iterClear.hasNext()) {
        iterClear.next();
        if(!diffPointsUSRP.contains(iterClear.key())){
            diffPointsOmega.remove(iterClear.key());
        }
    }
    MapUSRP = MakingMiddle(diffPointsUSRP);
    MapOmega = MakingMiddle(diffPointsOmega);
    QList <float> ListForCalc;
    QMapIterator<int, QPointF> iterDiff(MapUSRP);
    while (iterDiff.hasNext()) {
        iterDiff.next();
        QPointF appendValue(iterDiff.value().x(),iterDiff.value().y()-MapOmega.value(iterDiff.key()).y());
        listDiff.append(appendValue);
        ListForCalc.append(appendValue.y());
    }
    float middleDiffVal = WidgetHelper::calculatemiddleValue(ListForCalc);
    ui->label_3->clear();
    ui->label_3->setText(QString::number(middleDiffVal));
    LimitsDiffXY = calculateLimits(listDiff);
    return listDiff;
}

QMap<int, QPointF> Plot::MakingMiddle(QMultiMap<int, QPointF> points)
{
    QMap <int, QPointF> listPoints;
    QMultiMapIterator <int, QPointF> iter(points);
    while (iter.hasNext()) {
        iter.next();
        QList<QPointF> list = points.values(iter.key());
        float summ = 0;
        QListIterator<QPointF> listIter(list);
        while(listIter.hasNext()){
            summ = summ + listIter.next().y();
        }
        float middleValue = summ / list.size();
        QPointF insVal(list.first().x(),middleValue);
        if(!listPoints.contains(iter.key())){
            listPoints.insert(iter.key(),insVal);
        }
    }
    return listPoints;
}

QPair<QPair<float, float>, QPair<float, float> > Plot::calculateLimits(QList<QPointF> points)
{
    QPair<QPair<float, float>, QPair<float, float> > lim;
    if(!points.isEmpty()) {
        QListIterator <QPointF> iter(points);
        while (iter.hasNext()) {
            QPointF point = iter.next();
            if(point.y() > lim.second.second){
                lim.second.second = point.y();
            }
            if(point.y()<lim.second.first){
                lim.second.first = point.y();
            }
        }
        auto buff = qMakePair(points.first(),points.last());
        lim.first.first=buff.first.x();
        lim.first.second=buff.second.x();
    }
    return lim;
}

QList<QPointF> Plot::calculateSvertka(QList<QPointF> firstfunction, QList<QPointF> secondfunction)
{
    NormalizeValueCorrelation = firstfunction.size();
    QList<QPointF> resultat;
    QMap<int,QPointF> resultatBuff;
    int SizeA = firstfunction.size();
    int SizeB = secondfunction.size();
    QList<QPointF> R;
    int MaxPoints =0;
    for (int i = 0; i <= SizeA; i++) {
        QList<QPointF> Buffa;
        QList <QPointF> BuffB;
        for (int ik = 0; ik < i; ik++)
        {
            Buffa.push_front(firstfunction.at(ik));
            BuffB.append(secondfunction.at(ik));
        }
        float BuffR =0;
        for(int j=0;j<i;j++){
            BuffR = BuffR + (Buffa.at(j).y()*BuffB.at(j).y());
        }
        resultatBuff.insert(i,QPointF((float)i,BuffR));
        MaxPoints++;
    }
    for(int i= SizeA-1;i>=0;i--){
        QList<QPointF> Buffa;
        QList<QPointF> Buffb;
        for (int ik = i; ik>0; ik--)
        {
            Buffa.push_front(firstfunction.at(SizeA-ik));
            Buffb.append(secondfunction.at(SizeA-ik));
        }
        int BuffR = 0;
        for(int j=0;j<i;j++){
            BuffR = BuffR + (Buffa.at(j).y()*Buffb.at(j).y());
        }
        resultatBuff.insert(2*MaxPoints - i,QPointF((float)2*MaxPoints - i,BuffR));
    }
    resultat = WidgetHelper::makeList(resultatBuff);
    return resultat;
}

float Plot::calculateKoeffCorellation(QList<QPointF> firstfunction, QList<QPointF> secondfunction)
{
    float sum_X = 0, sum_Y = 0, sum_XY = 0;
        float squareSum_X = 0, squareSum_Y = 0;

        for (int i = 0; i < firstfunction.size(); i++)
        {
            // sum of elements of array X.
            sum_X = sum_X + firstfunction[i].y();

            // sum of elements of array Y.
            sum_Y = sum_Y + secondfunction[i].y();;

            // sum of X[i] * Y[i].
            sum_XY = sum_XY +firstfunction[i].y() * secondfunction[i].y();

            // sum of square of array elements.
            squareSum_X = squareSum_X + firstfunction[i].y() * firstfunction[i].y();
            squareSum_Y = squareSum_Y + secondfunction[i].y() *secondfunction[i].y();
        }

        // use formula for calculating correlation coefficient.
        float corr = (float)(firstfunction.size() * sum_XY - sum_X * sum_Y)
            / sqrt((firstfunction.size() * squareSum_X - sum_X * sum_X)
                * (firstfunction.size() * squareSum_Y - sum_Y * sum_Y));

        return corr;
}

void Plot::setDirforSave(QString Dir) // необходимо добавить на 5 позицию папку результаты
{
    if(Dir.isEmpty()){
        return;
    }
    QStringList sl;
    sl = Dir.split("/",Qt::SkipEmptyParts);
    NameImage.append(sl.last());
    sl.removeLast();
    QString newElem("/Result/");
    QString resultPath;
    auto iter = sl.begin();
    auto iter2 = sl.end();
    for(iter;iter!=sl.end();iter++){
        if(iter!=iter2){
            if(*iter!="EperimentsData"){
                resultPath.append(*iter);
                resultPath.append("/");}
            else {
                resultPath.append(*iter);
                resultPath.append(newElem);
            }
        } else{
            resultPath.append(*iter);
        }
    }
    SavePath = resultPath;
}

void Plot::MakePlot()
{
    ChartUSRP->removeAllSeries();
    ChartOmega->removeAllSeries();
    ChartDiff->removeAllSeries();
    ChartCorellation->removeAllSeries();
    QPair<int,int> XLim = DataBase->getXLimites();
    QPair<int,int> YLim = DataBase->getYLimites();
    QMap<int, QPointF> PointsOmega = DataBase->getPointsOmega();
    QMap<int, QPointF> PointsUSRP  = DataBase->getPointsUSRP();

    if((XLim == qMakePair(0,0))||(YLim == qMakePair(0,0)))

        return;

    auto *lsOmega = new QLineSeries;
    auto *lsUSRP = new QLineSeries;
    auto *lsdiff = new QLineSeries;
    auto *lsCorellation = new QLineSeries;

    listCorrel = calculateSvertka(WidgetHelper::makeList(MapUSRP),WidgetHelper::makeList(MapOmega));
    float valCorrel = calculateKoeffCorellation(WidgetHelper::makeList(MapUSRP),WidgetHelper::makeList(MapOmega));
    ui->label_5->clear();
    ui->label_5->setText(QString::number(valCorrel));
    LimitsCorrelationXY = calculateLimits(listCorrel);

    lsOmega->append(LinesAppend(PointsOmega));
    lsUSRP->append(LinesAppend(PointsUSRP));
    lsdiff->append(CalculatePlotdiff(PointsOmega,PointsUSRP));
    //DataBase::write_points_from_file(MapUSRP,MapOmega);
    lsCorellation->append(listCorrel);

    ChartOmega->addSeries(lsOmega);

    ChartOmega->createDefaultAxes();
    ChartOmega->axes(Qt::Horizontal).first()->setRange(XLim.first,XLim.second);
    ChartOmega->axes(Qt::Horizontal).first()->setTitleText("[МГц]");
    ChartOmega->axes(Qt::Vertical).first()->setRange(YLim.first,YLim.second);
    ChartOmega->axes(Qt::Vertical).first()->setTitleText("[ДБ]");
    ChartOmega->setTitle("Омега");

    ChartOmega->setMinimumSize(1000,500);

    ChartUSRP->addSeries(lsUSRP);

    ChartUSRP->createDefaultAxes();
    ChartUSRP->axes(Qt::Horizontal).first()->setRange(XLim.first,XLim.second);
    ChartUSRP->axes(Qt::Horizontal).first()->setTitleText("[МГЦ]");
    ChartUSRP->axes(Qt::Vertical).first()->setRange(YLim.first,YLim.second);
    ChartUSRP->axes(Qt::Vertical).first()->setTitleText("[ДБ]");
    ChartUSRP->setTitle("USRP");

    ChartUSRP->setMinimumSize(1000,500);

    ChartDiff->addSeries(lsdiff);

    ChartDiff->createDefaultAxes();
    ChartDiff->axes(Qt::Horizontal).first()->setRange(LimitsDiffXY.first.first,LimitsDiffXY.first.second);
    ChartDiff->axes(Qt::Horizontal).first()->setTitleText("[МГЦ]");
    ChartDiff->axes(Qt::Vertical).first()->setRange(LimitsDiffXY.second.first-5,LimitsDiffXY.second.second+5);
    ChartDiff->axes(Qt::Vertical).first()->setTitleText("[ДБ]");
    ChartDiff->setTitle("Разностный график");

    ChartDiff->setMinimumSize(1000,500);

    ChartCorellation->addSeries(lsCorellation);

    ChartCorellation->createDefaultAxes();
    ChartCorellation->axes(Qt::Horizontal).first()->setRange(LimitsCorrelationXY.first.first,LimitsCorrelationXY.first.second);
    ChartCorellation->axes(Qt::Horizontal).first()->setTitleText("[МГЦ]");
    ChartCorellation->axes(Qt::Vertical).first()->setRange(LimitsCorrelationXY.second.first-5,LimitsCorrelationXY.second.second+5);
    ChartCorellation->axes(Qt::Vertical).first()->setTitleText("[ДБbkj]");
    ChartCorellation->setTitle("Корредяционная функция");

    ChartCorellation->setMinimumSize(1000,500);

}

void Plot::MakeScreen(QWidget *widg)
{
    QPixmap pixmap(widg->size()) /*= QPixmap::grabWidget(widg)*/;
    widg->render(&pixmap);
    DataBase->write_points_from_file(MapUSRP,MapOmega);
    QDir dir(SavePath);
    if(!dir.exists()){
        dir.mkpath(SavePath);
    }

    QString fullath(SavePath);
    fullath.append(NameImage);
    QStringList newList = fullath.split(".");
    fullath.clear();
    int a = newList.size();
    for(int i =0;i<a-1; i++){
        fullath.append(newList.value(i));
    }
    fullath.append(".png");
    QFile File(fullath);
    if(File.open(QIODevice::WriteOnly)){
        qDebug()<<"Файл для сохранения открылся";
        pixmap.save(&File);
    } else {
        qDebug()<<"Файл для сохранение не был открыт"<<fullath;
        QMessageBox MB;
        MB.setText("Файл для сохранения не создан!\n"
                   "Невозможно сихранить результаты рассчетов");
        MB.exec();
    }
}

void Plot::BufFunctByMakeScreen()
{
    MakeScreen(ui->scrollArea_2);
}
