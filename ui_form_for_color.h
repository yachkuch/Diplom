/********************************************************************************
** Form generated from reading UI file 'form_for_color.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_FOR_COLOR_H
#define UI_FORM_FOR_COLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_for_color
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ButtonOk;
    QPushButton *ButtonCancel;

    void setupUi(QWidget *Form_for_color)
    {
        if (Form_for_color->objectName().isEmpty())
            Form_for_color->setObjectName("Form_for_color");
        Form_for_color->resize(240, 320);
        verticalLayout_2 = new QVBoxLayout(Form_for_color);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(Form_for_color);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label = new QLabel(frame);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");

        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addWidget(frame);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        frame_2 = new QFrame(Form_for_color);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        ButtonOk = new QPushButton(frame_2);
        ButtonOk->setObjectName("ButtonOk");

        horizontalLayout_2->addWidget(ButtonOk);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        ButtonCancel = new QPushButton(frame_2);
        ButtonCancel->setObjectName("ButtonCancel");

        horizontalLayout_3->addWidget(ButtonCancel);


        verticalLayout_2->addWidget(frame_2);


        retranslateUi(Form_for_color);

        QMetaObject::connectSlotsByName(Form_for_color);
    } // setupUi

    void retranslateUi(QWidget *Form_for_color)
    {
        Form_for_color->setWindowTitle(QCoreApplication::translate("Form_for_color", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form_for_color", "\320\222\321\213\320\261\320\270\321\200\320\260\320\265\320\274\321\213\320\271 \321\206\320\262\320\265\321\202", nullptr));
        ButtonOk->setText(QCoreApplication::translate("Form_for_color", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("Form_for_color", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_for_color: public Ui_Form_for_color {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_FOR_COLOR_H
