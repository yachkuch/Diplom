/********************************************************************************
** Form generated from reading UI file 'plot.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_H
#define UI_PLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Plot
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_9;
    QGraphicsView *graphicsView_5;
    QGraphicsView *graphicsView_6;
    QGraphicsView *graphicsView_7;
    QGraphicsView *graphicsView_8;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QRadioButton *radioButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pbStart;
    QPushButton *pbScreenshot;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Plot)
    {
        if (Plot->objectName().isEmpty())
            Plot->setObjectName("Plot");
        Plot->resize(964, 634);
        verticalLayout_2 = new QVBoxLayout(Plot);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(Plot);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFrameShape(QFrame::Box);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 936, 606));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        scrollArea_2 = new QScrollArea(scrollAreaWidgetContents);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 618, 2043));
        verticalLayout_9 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_9->setObjectName("verticalLayout_9");
        graphicsView_5 = new QGraphicsView(scrollAreaWidgetContents_3);
        graphicsView_5->setObjectName("graphicsView_5");
        graphicsView_5->setMinimumSize(QSize(0, 500));

        verticalLayout_9->addWidget(graphicsView_5);

        graphicsView_6 = new QGraphicsView(scrollAreaWidgetContents_3);
        graphicsView_6->setObjectName("graphicsView_6");
        graphicsView_6->setMinimumSize(QSize(0, 500));

        verticalLayout_9->addWidget(graphicsView_6);

        graphicsView_7 = new QGraphicsView(scrollAreaWidgetContents_3);
        graphicsView_7->setObjectName("graphicsView_7");
        graphicsView_7->setMinimumSize(QSize(0, 500));

        verticalLayout_9->addWidget(graphicsView_7);

        graphicsView_8 = new QGraphicsView(scrollAreaWidgetContents_3);
        graphicsView_8->setObjectName("graphicsView_8");
        graphicsView_8->setMinimumSize(QSize(0, 500));

        verticalLayout_9->addWidget(graphicsView_8);

        scrollArea_2->setWidget(scrollAreaWidgetContents_3);

        horizontalLayout->addWidget(scrollArea_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(frame_2);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFrameShape(QFrame::Box);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        radioButton = new QRadioButton(frame_2);
        radioButton->setObjectName("radioButton");
        radioButton->setAutoFillBackground(false);
        radioButton->setCheckable(true);

        verticalLayout_3->addWidget(radioButton);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_5->addItem(verticalSpacer_2);

        pbStart = new QPushButton(frame_2);
        pbStart->setObjectName("pbStart");

        verticalLayout_5->addWidget(pbStart);

        pbScreenshot = new QPushButton(frame_2);
        pbScreenshot->setObjectName("pbScreenshot");

        verticalLayout_5->addWidget(pbScreenshot);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");

        verticalLayout_5->addWidget(label_2);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");

        verticalLayout_5->addWidget(label_3);

        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");

        verticalLayout_5->addWidget(label_4);

        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");

        verticalLayout_5->addWidget(label_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        horizontalLayout->addWidget(frame_2);


        verticalLayout_4->addLayout(horizontalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Plot);

        QMetaObject::connectSlotsByName(Plot);
    } // setupUi

    void retranslateUi(QWidget *Plot)
    {
        Plot->setWindowTitle(QCoreApplication::translate("Plot", "Form", nullptr));
        label->setText(QCoreApplication::translate("Plot", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\276\320\262\320\265\320\264\320\265\320\275\320\270\320\265\320\274", nullptr));
        radioButton->setText(QCoreApplication::translate("Plot", "\320\235\320\260\320\273\320\270\321\207\320\270\320\265 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        pbStart->setText(QCoreApplication::translate("Plot", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        pbScreenshot->setText(QCoreApplication::translate("Plot", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 ", nullptr));
        label_2->setText(QCoreApplication::translate("Plot", "\320\241\321\200\320\265\320\264\320\275\320\265\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \321\200\320\260\320\267\320\275\320\276\321\201\321\202\320\270", nullptr));
        label_3->setText(QCoreApplication::translate("Plot", "0", nullptr));
        label_4->setText(QCoreApplication::translate("Plot", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \320\272\320\276\321\200\321\200\320\265\320\273\321\217\321\206\320\270\320\270", nullptr));
        label_5->setText(QCoreApplication::translate("Plot", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Plot: public Ui_Plot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_H
