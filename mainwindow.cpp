#include "mainwindow.h"

#include <QCheckBox>
#include <QToolBar>
#include <QMenuBar>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    SelectionMemory();
    ParseColor();
    MakingWorkWindow();
    this->setMinimumSize(QSize(1700,500));
}

MainWindow::~MainWindow()
{
}

void MainWindow::gettingCoordFromScroll(QPointF coord)
{
    if(ModeProggram == 0){
        static QPointF coord1;
        static QPointF coord2;

        SchetchicClics++;

        if(SchetchicClics<3){
            QPen pen((QColor(Qt::red)));
            pen.setWidth(1);
            if (SchetchicClics%2 ==1){

                line[0] = scene->addLine(0,coord.y(),image->size().width(),coord.y(),pen);
                line[1] = scene->addLine(coord.x(),0,coord.x(),image->size().height(),pen);

                QString text(QString::number(coord.x()));
                text.append(" ");
                text.append(QString::number(coord.y()));
                coord1 = coord;

                coordinates1->setText(text);

            } else {

                line[2] = scene->addLine(0,coord.y(),image->size().width(),coord.y(),pen);
                line[3] = scene->addLine(coord.x(),0,coord.x(),image->size().height(),pen);

                QString text(QString::number(coord.x()));
                text.append(" ");
                text.append(QString::number(coord.y()));
                coord2 = coord;

                coordinates2->setText(text);
                CalculateOtherPoints(coord1,coord2);

                if(!((coord1.x()<coord2.x()) && (coord1.y()>coord2.y()))){
                    QMessageBox MB;
                    MB.setText("Первая точка должна быть левым нижним углом, а вторая правым верхним!!!\n"
                               "ПРОГРАММА БУДЕТ РАБОТАТЬ НЕ КОРРЕКТНО!!!!!");
                    ResetTheCounter();
                    MB.exec();
                }

                //SchetchicClics = 0;
            }
        } else {
            QMessageBox MB;
            MB.setText("Границы анализа уже выбраны, для переопределения этих границ нажмите "
                       "кнопку Отменить");
            MB.exec();
        }
    } else if (ModeProggram == 1){
        QImage image2 = image->toImage();
        QColor col = getImageColor(image2,coord);
        FC->SetColorWindow(col);
        colorsBuffVector.append(col);
    }

}

void MainWindow::getSignalAboutforColor()
{
    QObject *sen = sender();
    QPushButton *pb = (QPushButton*) sen;
    if (pb->text()=="Применить"){
        //ModeProggram = 0;
        //FC->hide();
        ParseColor(1);
        if(!colorsVector.contains(colorsBuffVector.last())){
            colorsVector.append(colorsBuffVector.last());
        }
    } else {
        FC->hide();
        ModeProggram = 0;
    }
}

void MainWindow::ResetTheCounter()
{
    SchetchicClics = 0;
    coordinates1->clear();
    coordinates2->clear();
    coordinates3->clear();
    coordinates4->clear();
    for (int i=0;i<4;i++) {
        if(scene->items().contains(line[i])){
            scene->removeItem(line[i]);
            delete line[i];}
    }
}

void MainWindow::WritingLimits()
{
    QObject *obj = sender();

    int LimitValue;
    obj = static_cast<QTextEdit*>(obj);
    if(obj == EditXLeft){
        if(EditXLeft->document()->toRawText().toInt()!=0){
            LimitValue = EditXLeft->document()->toRawText().toInt();
            XLimits.first = LimitValue;
        } else {
            QMessageBox MB;
            MB.setText("Невозможно приобразовать значение нижнего предела оси "
                       "Х к целочисленному типу координат");
            MB.exec();
        }
    } else if(obj == EditXRight ){
        if(EditXRight->document()->toRawText().toInt()!=0){
            LimitValue = EditXRight->document()->toRawText().toInt();
            XLimits.second = LimitValue;
        } else {
            QMessageBox MB;
            MB.setText("Невозможно приобразовать значение верхнего предела оси "
                       "Х к целочисленному типу координат");
            MB.exec();
        }
    } else if(obj == EditYDown){
        if(EditYDown->document()->toRawText().toInt()!=0){
            LimitValue = EditYDown->document()->toRawText().toInt();
            YLimits.first = LimitValue;
        } else {
            QString str = EditYDown->document()->toRawText();
            if(str!="-"){
                QMessageBox MB;
                MB.setText("Невозможно приобразовать значение нижнего предела оси "
                           "У к целочисленному типу координат");
                MB.exec();
            }
        }
        //LimitValue = EditYDown->document()->toRawText().toInt();
    } else if(obj == EditYTop){
        if(EditYTop->document()->toRawText().toInt()!=0){
            LimitValue = EditYTop->document()->toRawText().toInt();
            YLimits.second = LimitValue;
        } else {
            QString str = EditYTop->document()->toRawText();
            if(str!="-"){
                QMessageBox MB;
                MB.setText("Невозможно приобразовать значение нижнего предела оси "
                           "У к целочисленному типу координат");
                MB.exec();
            }
        }
        // LimitValue = EditYTop->document()->toRawText().toInt();
    }
}

void MainWindow::RulActionForLines(bool val)
{
    auto *sen =static_cast<QAction*>(sender());

    QGraphicsLineItem *Line = getLineForButtom(sen);

    for (int i =0;i<4;i++) {
        if(scene->items().contains(line[i])){
            QPen pen((QColor(Qt::red)));
            line[i]->setPen(pen);
        }
    }

    if(val == false){
        return;

    } else {

        if(Line!=NULL){
            if(scene->items().contains(Line)){
                QPen pen((QColor(Qt::blue)));
                Line->setPen(pen);}
        }

        QListIterator<QAction*> iter(actions);
        while (iter.hasNext()) {
            QAction *act = iter.next();
            if(sen == act){
                act->setChecked(true);
            } else{
                act->setChecked(false);

            }
        }
    }
}

void MainWindow::SelectionMemory()
{
    Data_Base = new DataBase(this);
    FC = new Form_for_color();
    PlotWidget = new Plot(Data_Base);
    PlotWidget->show();
    FC->setWindowFlag(Qt::WindowStaysOnTopHint);
    FC->setParentWidget(this);
    scrollArea = new QScrollArea();
    image = new QPixmap();
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    PixmapItem = new QGraphicsPixmapItem;
    view->setScene(scene);
    view->show();

    connect(this,SIGNAL(clearDB()) , Data_Base , SLOT(ClearDatabase()));

    QFile fileWithSavePath("C:/Projects/Diplom/ReadPhotosGran/config/SavingImagePath.txt");
    fileWithSavePath.open(QIODevice::ReadOnly);
    if(fileWithSavePath.isOpen()){
        PatHByImaheGlon = fileWithSavePath.readLine();
        qDebug()<<PatHByImaheGlon;
        fileWithSavePath.close();
    } else {
        qDebug()<<QString("Не обнаружен файл конфигурации сохранения C:/Projects/Diplom/ReadPhotosGran/config/SavingImagePath.txt");

        QMessageBox mb;
        mb.setText("Не обнаружен файл конфигурации сохранения");
        mb.exec();
    }
    QString exp(PatHByImaheGlon);
    if(image->load(exp)){
        qDebug()<<"Изображение загружено";
        PairImagesPath.first = exp;
        PairImagesPath.second = MakeSecondPath(exp);
        workingRash.clear();
        workingRash.append(PatHByImaheGlon);
    } else {
        QMessageBox mb;
        mb.setText("Отсутствует данное изображение");
        mb.exec();
    }

}

void MainWindow::MakingWorkWindow()
{
    this->setCentralWidget(scrollArea);

    auto *toolBar = new QToolBar;

    auto *menuBar = new QMenuBar();
    auto menu = new QMenu("Меню");
    auto menuColor = new QMenu("Управление цветами");
    auto ActionFileDialog = new QAction("Открыть");
    ActionColor1 = new QAction("Добавить цвет");
    ActionColor2 = new QAction("Удалить все возможные цвета");
    QAction *ActionMakePair = new QAction("Сформировать парное значение фотографии");
    showWidgetPlot = new QAction("Графики");
    showWidgetAnalyzer = new QAction("Анализатор");
    auto menuRule = new QMenu("Управление линиями");
    menuColor->addAction(ActionColor1);
    menuColor->addAction(ActionColor2);
    menu->addMenu(menuColor);
    menuBar->addMenu(menu);
    menu->addAction(ActionFileDialog);
    menu->addAction(ActionMakePair);
    menu->addMenu(menuRule);
    QList<QAction*> list = {showWidgetAnalyzer};
    QList<QAction*> list2 = {showWidgetPlot};
    menuBar->addActions(list);
    menuBar->addActions(list2);

    connect(ActionFileDialog, SIGNAL(triggered(bool)), this, SLOT(FileDialogOpen(bool)));
    connect(ActionColor1, SIGNAL(triggered(bool)), this, SLOT(ConnectorForColorParser(bool)));
    connect(ActionColor2, SIGNAL(triggered(bool)), this, SLOT(ConnectorForColorParser(bool)));
    connect(ActionMakePair, SIGNAL(triggered(bool)), this, SLOT(rewritingImagePair(bool)));
    connect(showWidgetPlot,SIGNAL(triggered(bool)), this , SLOT(rooleMainWindow(bool)));
    connect(showWidgetAnalyzer,SIGNAL(triggered(bool)), this , SLOT(rooleMainWindow(bool)));

    for (int i=1;i<5;i++) {
        QAction *act = new QAction(QString("Линия %0").arg(i));
        act->setCheckable(true);
        connect(act,SIGNAL(triggered(bool)),this,SLOT(RulActionForLines(bool)));
        actions.append(act);
    }

    menuRule->addActions(actions);

    toolBar->addWidget(menuBar);

    this->addToolBar(toolBar);

    QVBoxLayout *mainLay = new QVBoxLayout();
    QVBoxLayout *mainLay2 = new QVBoxLayout();
    mainFrame = new QFrame();
    mainFrame->setAutoFillBackground(1);
    mainFrame->setLayout(mainLay2);

    mainLay->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    QLabel *lb_with_instruction = new QLabel();
    QLabel *lb_pixmap = new QLabel();
    QFont font_instructopn("Times", 10, QFont::Bold);
    font_instructopn.setItalic(1);
    lb_with_instruction->setFont(font_instructopn);
    lb_with_instruction->setAlignment(Qt::AlignCenter);

    QFrame *fr_inst = new QFrame;
    QVBoxLayout *l_fr_inst  = new QVBoxLayout();
    fr_inst->setFrameStyle(QFrame::Box);
    fr_inst->setLayout(l_fr_inst);
    fr_inst->setAutoFillBackground(1);
    l_fr_inst->addWidget(lb_with_instruction);
    fr_inst->setPalette(QPalette(QColor(Qt::blue)));

    scroll_forIm = new SCroll(this);

    QFrame *frame_Im = new QFrame();
    QVBoxLayout *frame_l = new QVBoxLayout();
    frame_Im->setFrameStyle(QFrame::Box);
    frame_Im->setLayout(frame_l);
    frame_l->addWidget(lb_pixmap);

    //qDebug()<<image->size().width()<<image->size().height();
    scroll_forIm->setMinimumWidth(1000);
    scroll_forIm->setMaximumHeight(768);
    scroll_forIm->setMaximumWidth(1000);
    scroll_forIm->setMinimumHeight(768);
    scroll_forIm->setWidgetResizable(1);

    scroll_forIm->setWidget(view);
    PixmapItem->setPixmap(*image);

    scene->addItem(PixmapItem);
    scene->setSceneRect(image->rect());

    QFrame *fr_buttons_andInform = new QFrame();
    QVBoxLayout *L_buttons_and_Inform = new QVBoxLayout();
    fr_buttons_andInform->setLayout(L_buttons_and_Inform);

    QWidget *widgButtins = MakingWidgetButtonsBycoord();
    widgButtins->setMaximumWidth(400);
    L_buttons_and_Inform->addWidget(widgButtins);


    QHBoxLayout *l_unite = new QHBoxLayout();
    QFrame *fr_unite = new QFrame();
    fr_unite->setFrameStyle(QFrame::Box);
    fr_unite->setLayout(l_unite);

    l_unite->addSpacing(20);
    l_unite->addWidget(scroll_forIm);
   // l_unite->addSpacing(20);
    l_unite->addWidget(fr_buttons_andInform);
   // l_unite->addSpacing(20);

    lb_with_instruction->setText("Программа по считыванию границ инициализированной области \n"
                                 "Первой отмечается нижняя левая точка, программа обозначит границы, "
                                 "далее выбираем верхнюю правую границу");

    scrollArea->setLayout(mainLay);

    mainLay->addWidget(mainFrame,30,Qt::AlignHCenter);
    mainLay ->addWidget(PlotWidget);

    PlotWidget->hide();

    mainLay2->addWidget(fr_inst);
   // mainLay2->addSpacing(30);
    mainLay2->addWidget(fr_unite);
}

QWidget *MainWindow::MakingWidgetButtonsBycoord()
{
    auto *MainFrame = new QFrame;
    auto *MainL = new QVBoxLayout();

    MainFrame->setFrameStyle(QFrame::Box);
    MainFrame->setLayout(MainL);

    auto *frame_lb_coord1 = new QFrame;
    auto *frame_lb_coord2 = new QFrame;
    auto *frame_lb_coord3 = new QFrame;

    frame_lb_coord1->setFrameStyle(QFrame::Box);
    frame_lb_coord2->setFrameStyle(QFrame::Box);
    frame_lb_coord3->setFrameStyle(QFrame::Box);

    auto *frame_textEd1 = new QFrame();
    auto *frame_textEd2 = new QFrame();

    frame_textEd1->setFrameStyle(QFrame::Box);
    frame_textEd2->setFrameStyle(QFrame::Box);

    auto l_frame_textEd1 = new QVBoxLayout();
    auto l_frame_textEd2 = new QVBoxLayout();

    frame_textEd1->setLayout(l_frame_textEd1);
    frame_textEd2->setLayout(l_frame_textEd2);

    auto *lay_coord_1 = new QHBoxLayout;
    auto *lay_coord_2 = new QHBoxLayout;
    auto *lay_coord_3 = new QHBoxLayout;

    lay_coord_1->setAlignment(Qt::AlignCenter);
    lay_coord_2->setAlignment(Qt::AlignCenter);
    lay_coord_3->setAlignment(Qt::AlignCenter);

    frame_lb_coord1->setLayout(lay_coord_1);
    frame_lb_coord2->setLayout(lay_coord_2);
    frame_lb_coord3->setLayout(lay_coord_3);

    coordinates1 = new QTextEdit();
    coordinates2 = new QTextEdit();
    coordinates3 = new QTextEdit();
    coordinates4 = new QTextEdit();

    coordinates1->setMaximumHeight(30);
    coordinates2->setMaximumHeight(30);
    coordinates3->setMaximumHeight(30);
    coordinates4->setMaximumHeight(30);

    coordinates1->setMaximumWidth(300);
    coordinates2->setMaximumWidth(300);
    coordinates3->setMaximumWidth(300);
    coordinates4->setMaximumWidth(300);

    auto *l_forTexEd1 = new QLabel("Левая нижняя точка");
    auto *l_forTexEd2 = new QLabel("Правая верхняя точка");
    auto *l_forTexEd3 = new QLabel("Левая верхняя точка");
    auto *l_forTexEd4 = new QLabel("Правая нижняя точка");

    l_frame_textEd1->addWidget(l_forTexEd1);
    l_frame_textEd1->addWidget(coordinates1);
    l_frame_textEd1->addWidget(l_forTexEd2);
    l_frame_textEd1->addWidget(coordinates2);
    l_frame_textEd2->addWidget(l_forTexEd3);
    l_frame_textEd2->addWidget(coordinates3);
    l_frame_textEd2->addWidget(l_forTexEd4);
    l_frame_textEd2->addWidget(coordinates4);

    auto *lb_coord1 = new QLabel();
    auto *lb_coord2 = new QLabel();
    auto *lb_coord3 = new QLabel();

    lb_coord2->setText("Координаты в которых происходит сканирование");
    lb_coord1->setText("Координаты выбранных точек");
    lb_coord3->setText("Действия");

    auto *pb1 = new QPushButton("Применить график");
    auto *pb2 = new QPushButton("Отменить");

    connect(pb2, SIGNAL(clicked()),this, SLOT(ResetTheCounter()));
    connect(pb1, SIGNAL(clicked()), this, SLOT(FormingInform()));
    connect(pb1,SIGNAL(clicked()) ,PlotWidget ,SLOT(MakePlot()));
    //connect(pb1, SIGNAL(clicked()), this, SLOT(FormingInform()));
    connect(this,SIGNAL(InformationForCount( QPointF, QPointF, QPair<int, int>, QPair<int,int> , QMultiMap<int,QPointF>,int)),Data_Base,SLOT(setInformation( QPointF, QPointF, QPair<int, int> , QPair<int,int>  , QMultiMap<int,QPointF>, int )));

    auto *pbLay = new QHBoxLayout();

    pbLay->addWidget(pb1);
    pbLay->addWidget(pb2);

    auto *frame_pb = new QFrame();
    frame_pb->setFrameStyle(QFrame::Box);
    frame_pb->setLayout(pbLay);

    lay_coord_1->addWidget(lb_coord1);
    lay_coord_2->addWidget(lb_coord2);
    lay_coord_3->addWidget(lb_coord3);

    MainL->addWidget(frame_lb_coord1);
    MainL->addWidget(frame_textEd1);
    MainL->addWidget(frame_lb_coord2);
    MainL->addWidget(frame_textEd2);
    MainL->addWidget(MakingLimits());
    MainL->addWidget(frame_lb_coord3);
    MainL->addWidget(frame_pb);

    return MainFrame;
}

QWidget *MainWindow::MakingLimits()
{
    EditXLeft = new QTextEdit;
    EditXRight = new QTextEdit;
    EditYTop = new QTextEdit;
    EditYDown = new QTextEdit;

    connect(EditXLeft, SIGNAL(textChanged()) , this , SLOT(WritingLimits()));
    connect(EditXRight, SIGNAL(textChanged()) , this , SLOT(WritingLimits()));
    connect(EditYTop, SIGNAL(textChanged()) , this , SLOT(WritingLimits()));
    connect(EditYDown, SIGNAL(textChanged()) , this , SLOT(WritingLimits()));

    auto MainL = new QVBoxLayout;
    auto *MainF = new QFrame;

    // MainF->setFrameStyle(QFrame::Box);

    auto label_withNames = new QLabel;
    auto frForLabel = new QFrame;
    auto layForName = new QVBoxLayout;

    label_withNames->setText("Пределы шкал");
    frForLabel->setFrameStyle(QFrame::Box);
    frForLabel->setLayout(layForName);
    layForName->addWidget(label_withNames);

    auto label_withNamesXLeft = new QLabel;
    auto label_withNamesXRight = new QLabel;
    auto frForLabelX = new QFrame;
    auto layForNameX = new QHBoxLayout;

    label_withNamesXLeft->setText("Ось X Нижняя граница");
    label_withNamesXRight->setText("Ось X Верхняя граница");
    frForLabelX->setFrameStyle(QFrame::Box);
    frForLabelX->setLayout(layForNameX);
    layForNameX->addWidget(label_withNamesXLeft);
    layForNameX->addWidget(EditXLeft);
    layForNameX->addWidget(label_withNamesXRight);
    layForNameX->addWidget(EditXRight);
    EditXLeft->setMaximumHeight(30);
    EditXRight->setMaximumHeight(30);

    auto label_withNamesYDown = new QLabel;
    auto label_withNamesYTop = new QLabel;
    auto frForLabely = new QFrame;
    auto layForNamey = new QHBoxLayout;

    label_withNamesYDown->setText("Ось Y Нижняя граница");
    label_withNamesYTop->setText("Ось Y Верхняя граница");
    frForLabely->setFrameStyle(QFrame::Box);
    frForLabely->setLayout(layForNamey);
    layForNamey->addWidget(label_withNamesYDown);
    layForNamey->addWidget(EditYDown);
    layForNamey->addWidget(label_withNamesYTop);
    layForNamey->addWidget(EditYTop);
    EditYDown->setMaximumHeight(30);
    EditYDown->setMinimumHeight(30);
    EditYTop->setMaximumHeight(30);
    EditYTop->setMinimumHeight(30);

    MainF->setLayout(MainL);

    MainL->addWidget(frForLabel);
    MainL->addWidget(frForLabelX);
    MainL->addWidget(frForLabely);

    return MainF;
}

void MainWindow::CalculateOtherPoints(QPointF LeftDownPoint, QPointF RightTopPoint)
{
    QString text(QString::number(LeftDownPoint.x()));
    text.append(" ");
    text.append(QString::number(RightTopPoint.y()));
    coordinates3->setText(text);
    text.clear();
    text.append(QString::number(RightTopPoint.x()));
    text.append(" ");
    text.append(QString::number(LeftDownPoint.y()));
    coordinates4->setText(text);
    LeftdownPoint = LeftDownPoint;
    RighttopPoint = RightTopPoint;
}

void MainWindow::setValueonEdit()
{
    QString text(QString::number(LeftdownPoint.x()));
    text.append(" ");
    text.append(QString::number(LeftdownPoint.y()));
    coordinates1->setText(text);
    text.clear();
    text.append(QString::number(RighttopPoint.x()));
    text.append(" ");
    text.append(QString::number(RighttopPoint.y()));
    coordinates2->setText(text);
}

const QAction *MainWindow::getCheckedAct()
{
    QListIterator<QAction*> iter(actions);
    while (iter.hasNext()) {
        QAction *act = iter.next();
        if(act->isChecked() == true){
            return act;
        }
    }
    QAction *act = NULL;

    return act;
}

QGraphicsLineItem *MainWindow::getLineForButtom(const QAction *act)
{
    QString str = act->text();
    str.remove(0,5);
    return line[str.toInt()-1];
}

bool MainWindow::getOrientationLine(QGraphicsLineItem *Line)
{
    for (int i=0;i<4;i++) {
        if(line[i] == Line){
            if(i%2 == 0){
                return true;
            } else {
                return false;
            }
        }
    }
    QMessageBox MB;
    MB.setText("Функция getOrientation Не имеет такой линии");
    MB.exec();
    return true;
}

QColor MainWindow::getImageColor(QImage image,QPointF coord)
{
    QPointF itemPoint = PixmapItem->mapToItem(PixmapItem,coord);
    return image.pixelColor(itemPoint.toPoint());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->type() == QEvent::KeyPress){

        const QAction *act = getCheckedAct();

        if(act==NULL){
            return;
        }
        QGraphicsLineItem *line = getLineForButtom(act);
        QPointF coordinates = line->scenePos();
        bool orienttion = getOrientationLine(line);
        int numberLine = NumberLine(line);

        if(orienttion == false){
            if (event->key() == Qt::Key_A)
            {
                line->setPos(coordinates.x()-1,coordinates.y());
                if(numberLine == 1){
                    lineMoving(&LeftdownPoint,-1,0);
                    setValueonEdit();
                    CalculateOtherPoints(LeftdownPoint,RighttopPoint);
                } else if (numberLine==3){
                    lineMoving(&RighttopPoint,-1,0);
                    setValueonEdit();
                    CalculateOtherPoints(LeftdownPoint,RighttopPoint);
                }

                //gettingCoordFromScroll();
            }
            else if (event->key() == Qt::Key_D)
            {
                line->setPos(coordinates.x()+1,coordinates.y());
                if(numberLine == 1){
                    lineMoving(&LeftdownPoint,1,0);
                    setValueonEdit();
                    CalculateOtherPoints(LeftdownPoint,RighttopPoint);
                } else if (numberLine==3){
                    lineMoving(&RighttopPoint,1,0);
                    setValueonEdit();
                    CalculateOtherPoints(LeftdownPoint,RighttopPoint);
                }

                //gettingCoordFromScroll();
            }
        } else {
            if (event->key() == Qt::Key_S)
            {
                line->setPos(coordinates.x(),coordinates.y()+1);
                if(numberLine == 0){
                    lineMoving(&LeftdownPoint,0,-1);
                    setValueonEdit();
                    CalculateOtherPoints(LeftdownPoint,RighttopPoint);
                } else if (numberLine==2){
                    lineMoving(&RighttopPoint,0,-1);
                    setValueonEdit();
                    CalculateOtherPoints(LeftdownPoint,RighttopPoint);
                }
                //gettingCoordFromScroll();
            }
            else if (event->key() == Qt::Key_W)
            {
                line->setPos(coordinates.x(),coordinates.y()-1);
                if(numberLine == 0){
                    lineMoving(&LeftdownPoint,0,1);
                    setValueonEdit();
                    CalculateOtherPoints(LeftdownPoint,RighttopPoint);
                } else if (numberLine==2){
                    lineMoving(&RighttopPoint,0,1);
                    setValueonEdit();
                    CalculateOtherPoints(LeftdownPoint,RighttopPoint);
                }
                //gettingCoordFromScroll();
            }
        }
    }
}

void MainWindow::lineMoving(QPointF *point, int dx, int dy)
{
    if((point->x() == 0)||(point->y() == 0)){
        return;
    }
    point->setX(point->x()+dx);
    point->setY(point->y()+dy);
    CalculateOtherPoints(LeftdownPoint, RighttopPoint);
}

int MainWindow::NumberLine(const QGraphicsLineItem *Line)
{
    for (int i=0;i<4;i++) {
        if(line[i]==Line) return i;
    }
    QMessageBox MB;
    MB.setText("Нет такое линии NumberLine");
    return 0;
}

void MainWindow::Sender() // проверить данное логическое выражение оно не работает
{
    if((XLimits==qMakePair(0,0))||(YLimits==qMakePair(0,0))||(LeftdownPoint==QPointF(0,0))||(RighttopPoint==QPointF(0,0))
            ||(points.isEmpty())){
        QMessageBox MB;
        MB.setText("Набор точек не может быть отправлен на опбработку, какой-то из параметров пуст");
    } else {
        int type;
        QStringList str = workingRash.split(".");
        if (str.last() == "jpg"){
            type = 1;
        } else if (str.last()=="bmp"){
            type = 2;
        }
        emit(InformationForCount(LeftdownPoint,RighttopPoint,XLimits,YLimits,points,type));
        points.clear();
        // Необходимо после отправки добавить очистку полей и с сигналом сформировать уникальный id фото
    }
}

void MainWindow::ParseColor(int scenaryWOrk)
{
    QString path("C:/Projects/Diplom/ReadPhotosGran/config/");
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath(path);
    }
    QString nameFile("GraphicsColors.txt");
    QString fullath(path);
    fullath.append(nameFile);
    QFile File(fullath);
    switch (scenaryWOrk) {
    case 0:
        if(File.open(QIODevice::ReadOnly)){
            qDebug()<<"Файл c рабочими цветами открылся";
            QTextStream in(&File);
            in.readLine();
            while (in.atEnd() == false) {
                QString Buff = in.readLine();
                if(!Buff.isEmpty()){
                    QStringList BuffList = Buff.split(" ");
                    QColor color(BuffList[0].toInt(),BuffList[1].toInt(),BuffList[2].toInt());
                    if(!colorsVector.contains(color)){
                        colorsVector.append(color);
                    }
                }
            }

        } else {
            qDebug()<<"Файл c рабочими цветами не открылся";
            QMessageBox MB;
            MB.setText("Файл c рабочими цветами не открылся"
                       "Был создан новый файл цветов, необходимо выбрать цвета,"
                       "для проведения анализа!");
            MB.exec();
            File.open(QIODevice::WriteOnly);
            QTextStream out(&File);
            out<<"R"<<" "<<"G"<<" "<<"B"<<"\r\n";
        }
        break;
    case 1:
        if(File.open(QIODevice::WriteOnly)){
            qDebug()<<"Файл c рабочими цветами открылся";
            File.remove();
            QFile File1(fullath);
            QTextStream out(&File1);
            if(File1.open(QIODevice::WriteOnly)){
                out<<"R"<<" "<<"G"<<" "<<"B"<<"\r\n";
                QVectorIterator <QColor> iter(colorsVector);
                while (iter.hasNext()) {
                    //if(iter!= colorsVector.last()) НУЖНА ПРОВЕРКА НА ПОСЛЕДНЕМ ЭЛЕМЕНТЕ НЕ НУЖЕН ENDL МОЖЕТ ЕБАНУТЬСЯ!!!!
                    QColor Buff = iter.next();
                    out<<Buff.red()<<" "<<Buff.green()<<" "<<Buff.blue()<<"\r\n";
                }
            }
            File1.close();
        } else {
            qDebug()<<"Файл c рабочими цветами не открылся";
            QMessageBox MB;
            MB.setText("Файл c рабочими цветами не открылся");
            MB.exec();
        }
        break;
    case 2:
        if(File.open(QIODevice::ReadWrite)){
            qDebug()<<"Файл c рабочими цветами удален";
            File.remove();
        } else {
            qDebug()<<"Файл c рабочими цветами не открылся";
            QMessageBox MB;
            MB.setText("Файл c рабочими цветами не открылся");
            MB.exec();
        }
        break;
    }
    File.close();
}

QString MainWindow::MakeSecondPath(QString path) // Лишний кусочек в адресе и еще лишний слеш в конце
{
    QString SecondPath;
    QStringList listPath = path.split("/");
    if(listPath.at(5) == "exp yak"){
        listPath.removeAt(5);
        listPath.insert(5,"exp yakush");
        QString file = listPath.last();
        QStringList lastList = file.split(".");
        if(lastList.last() == "jpg"){
            QString bufL(lastList.first());
            bufL.append(".");
            bufL.append("bmp");
            listPath.removeAt(listPath.size()-1);
            listPath.append(bufL);
        } else if(lastList.last() =="bmp"){
            QString bufL(lastList.first());
            bufL.append(".");
            bufL.append("jpg");
            listPath.removeAt(listPath.size()-1);
            listPath.append(bufL);
        }

    } else if(listPath.at(5) == "exp yakush"){
        listPath.removeAt(5);
        listPath.insert(5,"exp yak");
        QString file = listPath.last();
        QStringList lastList = file.split(".");
        if(lastList.last() == "jpg"){
            QString bufL(lastList.first());
            bufL.append(".");
            bufL.append("bmp");
            listPath.removeAt(listPath.size()-1);
            listPath.append(bufL);
        } else if(lastList.last() =="bmp"){
            QString bufL(lastList.first());
            bufL.append(".");
            bufL.append("jpg");
            listPath.removeAt(listPath.size()-1);
            listPath.append(bufL);
        }

    }
    QStringListIterator iter(listPath);
    while(iter.hasNext()) {
        QString str(iter.next());
        SecondPath.append(str);
        if(str != listPath.last())
            SecondPath.append("/");
    }
    return  SecondPath;
}

void MainWindow::rooleMainWindow(bool)
{
    QAction *send = static_cast<QAction*>(sender());
    if(send == showWidgetPlot){
        mainFrame->hide();
        PlotWidget->show();

    } else if(send == showWidgetAnalyzer){
        mainFrame->show();
        PlotWidget->hide();
    }
}

void MainWindow::ConnectorForColorParser(bool)
{
    QObject *sen = sender();
    if((QAction*) sen == ActionColor1){
        FC->show();
        ModeProggram = 1;

    } else if ((QAction*)sen == ActionColor2){

        ParseColor(2);
    }
}

void MainWindow::rewritingImagePair(bool)
{
    scene->removeItem(PixmapItem);
    delete PixmapItem;
    delete image;
    image = new QPixmap;
    if(!image->load(PairImagesPath.second)){
        QMessageBox MB;
        MB.setText("Парный график не загружен, не найден файл!!!!!");
        MB.exec();
    }
    scene->setSceneRect(image->rect());
    PixmapItem = scene->addPixmap(*image);
    workingRash.clear();;
    workingRash.append(PairImagesPath.second);
    //qDebug()<<scene->width()<<scene->height();
    //!! После создания второй картинки необходимо очистить путь
}

void MainWindow::FormingInform()
{
    QImage image2 = image->toImage();
    QStringList workscenary = workingRash.split(".");
    //qDebug()<<workscenary.last();
    QPointF coordinats;
    for(int x=LeftdownPoint.x();x<=RighttopPoint.x();x++){
        coordinats.setX(x);
        for (int y=RighttopPoint.y();y<=LeftdownPoint.y();y++) {
            coordinats.setY(y);
            if(getImageColor(image2,coordinats).green()<180 && workscenary.last() == "jpg"){
                points.insert(coordinats.x(),coordinats);
            } else if(colorsVector.contains(getImageColor(image2,coordinats)) && workscenary.last() == "bmp"){
                points.insert(coordinats.x(),coordinats);
            }
        }
    }
    Sender();
}

void MainWindow::FileDialogOpen(bool)
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"C:/Projects/Diplom/ReadPhotosGran/EperimentsData");
    if(filename.isEmpty()) return;
    scene->removeItem(PixmapItem);
    delete PixmapItem;
    delete image;
    image = new QPixmap;
    image->load(filename);
    workingRash.clear();;
    workingRash.append(filename);
    PairImagesPath.first = filename;
    PairImagesPath.second = MakeSecondPath(filename);
    PixmapItem = scene->addPixmap(*image);
    PlotWidget->setDirforSave(filename);
    QFile fileWithSavePath("C:/Projects/Diplom/ReadPhotosGran/config/SavingImagePath.txt");
    fileWithSavePath.open(QIODevice::WriteOnly);
    if(fileWithSavePath.isOpen()){
        fileWithSavePath.write(filename.toUtf8());
        qDebug()<<PatHByImaheGlon;
        fileWithSavePath.close();
    } else {
        qDebug()<<"Не обнаружен файл конфигурации сохранения C:/Projects/Diplom/ReadPhotosGran/config/SavingImagePath.txt";
        QMessageBox mb;
        mb.setText("Не обнаружен файл конфигурации сохранения");
        mb.exec();
    }
    emit(clearDB());
}

