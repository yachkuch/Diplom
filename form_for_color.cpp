#include "form_for_color.h"
#include "ui_form_for_color.h"

Form_for_color::Form_for_color(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_for_color)
{
    ui->setupUi(this);
}

Form_for_color::~Form_for_color()
{
    delete ui;
}

void Form_for_color::setParentWidget(QWidget *parent)
{
    this->parent = parent;
    connect(ui->ButtonOk, SIGNAL(pressed()),parent,SLOT(getSignalAboutforColor()));
    connect(ui->ButtonCancel, SIGNAL(pressed()),parent,SLOT(getSignalAboutforColor()));
}

void Form_for_color::SetColorWindow(QColor color)
{
    MainColor = color;
    ui->frame->setStyleSheet(QString("background-color: rgb(%0,%1,%2)").arg(color.red()).arg(color.green()).arg(color.blue()));
}
