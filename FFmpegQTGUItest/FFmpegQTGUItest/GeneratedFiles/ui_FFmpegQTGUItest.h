/********************************************************************************
** Form generated from reading UI file 'FFmpegQTGUItest.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFMPEGQTGUITEST_H
#define UI_FFMPEGQTGUITEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <playview.h>

QT_BEGIN_NAMESPACE

class Ui_FFmpegQTGUItestClass
{
public:
    QWidget *centralWidget;
    PlayView *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLabel *label;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FFmpegQTGUItestClass)
    {
        if (FFmpegQTGUItestClass->objectName().isEmpty())
            FFmpegQTGUItestClass->setObjectName(QString::fromUtf8("FFmpegQTGUItestClass"));
        FFmpegQTGUItestClass->resize(600, 436);
        centralWidget = new QWidget(FFmpegQTGUItestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_2 = new PlayView(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 561, 291));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 14, 341, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(9);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(160, 350, 239, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        FFmpegQTGUItestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FFmpegQTGUItestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        FFmpegQTGUItestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FFmpegQTGUItestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        FFmpegQTGUItestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FFmpegQTGUItestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FFmpegQTGUItestClass->setStatusBar(statusBar);

        retranslateUi(FFmpegQTGUItestClass);

        QMetaObject::connectSlotsByName(FFmpegQTGUItestClass);
    } // setupUi

    void retranslateUi(QMainWindow *FFmpegQTGUItestClass)
    {
        FFmpegQTGUItestClass->setWindowTitle(QApplication::translate("FFmpegQTGUItestClass", "FFmpegQTGUItest", nullptr));
        label_2->setText(QString());
        pushButton->setText(QApplication::translate("FFmpegQTGUItestClass", "\346\211\223\345\274\200", nullptr));
        label->setText(QString());
        pushButton_2->setText(QApplication::translate("FFmpegQTGUItestClass", "\346\222\255\346\224\276", nullptr));
        pushButton_3->setText(QApplication::translate("FFmpegQTGUItestClass", "\346\210\252\345\261\217", nullptr));
        pushButton_4->setText(QApplication::translate("FFmpegQTGUItestClass", "\345\274\271\345\271\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FFmpegQTGUItestClass: public Ui_FFmpegQTGUItestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFMPEGQTGUITEST_H
