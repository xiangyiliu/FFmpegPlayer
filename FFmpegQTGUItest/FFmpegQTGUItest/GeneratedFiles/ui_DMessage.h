/********************************************************************************
** Form generated from reading UI file 'DMessage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DMESSAGE_H
#define UI_DMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DMessage
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QWidget *DMessage)
    {
        if (DMessage->objectName().isEmpty())
            DMessage->setObjectName(QString::fromUtf8("DMessage"));
        DMessage->resize(314, 30);
        horizontalLayout = new QHBoxLayout(DMessage);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(DMessage);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);


        retranslateUi(DMessage);

        QMetaObject::connectSlotsByName(DMessage);
    } // setupUi

    void retranslateUi(QWidget *DMessage)
    {
        DMessage->setWindowTitle(QApplication::translate("DMessage", "DMessage", nullptr));
        label->setText(QApplication::translate("DMessage", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DMessage: public Ui_DMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DMESSAGE_H
