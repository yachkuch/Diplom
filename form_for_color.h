#ifndef FORM_FOR_COLOR_H
#define FORM_FOR_COLOR_H

#include <QWidget>
#include <QColor>

namespace Ui {
class Form_for_color;
}

class Form_for_color : public QWidget
{
    Q_OBJECT

public:
    explicit Form_for_color(QWidget *parent = nullptr);
    ~Form_for_color();
    /**
     * @brief setParentWidget Устанавливает виджет с которым окно поддерживает коннекты
     * @param parent виджет верхнего уровня
     */
    void setParentWidget(QWidget *parent);
    /**
     * @brief SetColorWindow Устанавливает выбранный цвет на графике в окошко виджета
     * @param color вставляемый цвет
     */
    void SetColorWindow(QColor color);

private:
    Ui::Form_for_color *ui;

    QWidget *parent;
    // ! Установленный цвет выбранный на картинке
    QColor MainColor;
};

#endif // FORM_FOR_COLOR_H
