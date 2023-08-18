#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QLayout>
#include <QGraphicsItem>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QFrame>
#include <QSizePolicy>
#include <QPushButton>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QMap>
#include <QGraphicsItem>

// инклуд гипотетически работующей либы, но пока что хуй его знает
//#include <C:/Users/Никита/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense>

#include "widgethelper.h"
#include "scroll.h"
#include "database.h"
#include "plot.h"
#include "form_for_color.h"
//! Переменная для отключения вывода сообщений в дебагер
#define DebugMode 1;

/**
 * @brief The MainWindow class формирование главного
 * диалогового виджета1
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    /**
     * @brief gettingCoordFromScroll Слот получения координат в которых происходит анализ
     * @param coord Значение координат мыши на скролле
     */
    void gettingCoordFromScroll(QPointF coord);
    /**
     * @brief getSignalAboutforColor получает сигнал о считывании цвета
     */
    void getSignalAboutforColor();

private slots:

    /**
     * @brief ResetTheCounter Сбрасывает счетчик кликов
     */
    void ResetTheCounter();
    /**
     * @brief WritingLimits Записывает пределы шкалы проводимых измерений
     */
    void WritingLimits();
    /**
     * @brief RulActionForLines Управление кнопками разблокировки позиций линий
     */
    void RulActionForLines(bool);
    /**
     * @brief FormingInform Формирует информацию о графике для void Sender()
     */
    void FormingInform();
    /**
     * @brief FileDialogOpen Открывает рабочую директорию для работы с файлами
     */
    void FileDialogOpen(bool);
    /**
     * @brief ConnectorForColorParser Формирует управляющие команды для ParseColor
     */
    void ConnectorForColorParser(bool);
    /**
     * @brief rewritingImagePair Перезаписывает фото на новое, парно подходящее для анализа
     */
    void rewritingImagePair(bool);
    /**
     * @brief rooleMainWindow управляет главным окном приложения
     */
    void rooleMainWindow(bool);
    /**
     * @brief get_name функция вернет название текущей анализируекмой фотографии, необходимо для того, чтоб писать в файл названия по точкам
     * (обязательно необходимо, чтобы возвращаемое значение несло с собой и информацию о типе
     * модуляции, так как иначе в файле произойдет перетирвание и я не различу при построении в матлаб)
     * @return
     */
    QString get_name();

private:

    DataBase *Data_Base;
    //! Счетчик кликов по скролл арене
    int SchetchicClics = 0;
    //! Переменная определяет режим работы при значении 0 стандартный выбор положения
    //! границ анализа, при 1 происходит выбор цвета
    unsigned int ModeProggram = 0;
    //! Основная арена
    QScrollArea *scrollArea;
    //! Клавиши управления для работы с цветами
    QAction *ActionColor1;
    QAction *ActionColor2;
    //! Хранилище для картинки
    QPixmap *image;

    // Глваный виджет рамки
    QFrame *mainFrame;

    QGraphicsScene *scene;
    SCroll *scroll_forIm;
    QGraphicsView *view;

    //! Окно выбора цвет
    Form_for_color *FC;
    //! Линии обозначающие пределы анализа
    QGraphicsLineItem *line[4];
    QGraphicsPixmapItem *PixmapItem;

    //! Виджет в котором строятся графики
    Plot *PlotWidget;
    //! Виджеты в которые выводятся координаты и пределы анализа
    QTextEdit *coordinates1;
    QTextEdit *coordinates2;
    QTextEdit *coordinates3;
    QTextEdit *coordinates4;
    QTextEdit *EditXLeft;
    QTextEdit *EditXRight;
    QTextEdit *EditYDown;
    QTextEdit *EditYTop;
    //! Список кнопок разблокироки управления линиями
    QList <QAction*> actions;
    //! Хранилище пределов по оси х
    QPair<int, int> XLimits;
    //! Хранилище пределов по оси у
    QPair<int,int> YLimits;
    //! Координаты левой нижней точки
    QPointF LeftdownPoint;
    //! Координаты правой верхней точки
    QPointF RighttopPoint;
    //! Вектор координат точек графика
    QMultiMap <int,QPointF> points;
    //! Глобальное последнее значение открытой картинки графика
    QString PatHByImaheGlon;
    //! Хранилище всех используемых цветов в графиках
    QVector <QColor> colorsVector;
    //! Временное хранилище для поступающих с виджета цветов, в основное хранилище добавляется только
    //! последнее из буфера после подтверждения по кнопке, затем очищается
    QVector <QColor> colorsBuffVector;
    /**
     * @brief PairImagesPath Пара путей до графика
     */
    QPair <QString,QString> PairImagesPath;
    //! Расширение фотографии необходимое для выбора при каком условии будет считывать цвета анализатор
    QString workingRash;
    /**
     * @brief showWidgetPlot кнопка показывающая виджет с графиком
     */
    QAction *showWidgetPlot;
    /**
     * @brief showWidgetAnalyzer кнопка показывающая виджет с анализатором
     */
    QAction *showWidgetAnalyzer;

    /*********************Функции******************/

    /**
     * @brief SelectionMemory Функция выделения памяти
     */
    void SelectionMemory();
    /**
     * @brief MakingWorkWindow Формирование главного окна виджета
     */
    void MakingWorkWindow();
    /**
     * @brief MakingWidgetButtonsBycoord Формирование бокового виджета с кнопками и пределами
     * @return Полученный виджет
     */
    QWidget* MakingWidgetButtonsBycoord();
    QWidget* MakingLimits();
    /**
     * @brief CalculateOtherPoints Вычисление оставшихся двух точек пересечения линий
     * @param LeftDownPoint Левая нижняя точка
     * @param RightTopPoint Правая верхняя точка
     */
    void CalculateOtherPoints(QPointF LeftDownPoint, QPointF RightTopPoint);
    /**
     * @brief setValueonEdit Устанавливает значение первых двух эдитов
     */
    void setValueonEdit();
    /**
     * @brief getCheckedAct Функция возвращает кнопку которая разблокирует возможность перемещения линии
     * @return Нажатая кнопка
     */
    const QAction* getCheckedAct();
    /**
     * @brief getLineForButtom Возвращает итем линии соответствующей кнопке
     * @param act Кнопк
     * @return Итем линии
     */
    QGraphicsLineItem *getLineForButtom(const QAction* act);
    /**
     * @brief getOrientationLine Проверяет ориентацию линии горизонтальная или вертикальная
     * @param line Линию которую надо проанализировать
     * @return если 1 то вертикальная если 0 то горизонтальная
     */
    bool getOrientationLine(QGraphicsLineItem *Line);
    /**
     * @brief getImageColor Возвращает цвет пикселя действующей картинки
     * @param coord Координаты пикселя
     * @return цвет пикселя
     */
    QColor getImageColor(QImage image, QPointF coord);
    /**
     * @brief keyPressEvent Событие нажатие клавиши на клавиатуре
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * @brief lineMoving Изменяет значение при движении линии влево и вправо
     * @param dx смещение по оси x
     * @param dy смещение по оси y
     * @param point координаты
     */
    void lineMoving(QPointF *point,int dx,int dy);
    /**
     * @brief NumberLine Возвращает номер линии в зависимости от нажатой кнопки
     * @param act кнопка
     * @return номер линии
     */
    int NumberLine(const QGraphicsLineItem *act);
    /**
     * @brief Sender Отправляет информацию в базу на обработку и хранение
     */
    void Sender();
    /**
     * @brief ParseColor Читает или добавляет или перезаписывает файл с цветами используемыми
     *  при анализе графиков
     * @param scenaryWOrk 0 - читаем файл, 1 - добавляем цвет в файл, 2 - очищаем файл
     */
    void ParseColor(int scenaryWOrk = 0);
    /**
     * @brief MakeSecondPath Формирует второй путь до изображения
     * @param path путь до текущего
     * @return путь до нового
     */
    QString MakeSecondPath(QString path);

signals:
    /**
         * @brief InformationForCount
         * @param LeftdownPoint
         * @param RightTopPoint
         * @param XLimits
         * @param YLimitss
         * @param Points
         * @param TypeGraf тип графика если это 1 то график с форматом jpg и это usrp , если параметр 2 то это формат
         * bmp и это снимала omega
         */
        void InformationForCount( QPointF LeftdownPoint, QPointF RightTopPoint, QPair<int, int> XLimits, QPair<int,int> YLimitss , QMultiMap<int,QPointF> Points, int TypeGraf);
        /**
         * @brief clearDB Очистка базы данных
         */
        void clearDB();
};
#endif // MAINWINDOW_H
