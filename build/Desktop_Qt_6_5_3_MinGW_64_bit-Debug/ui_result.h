/********************************************************************************
** Form generated from reading UI file 'result.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULT_H
#define UI_RESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_result
{
public:
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_2;

    void setupUi(QDialog *result)
    {
        if (result->objectName().isEmpty())
            result->setObjectName("result");
        result->resize(982, 775);
        QFont font;
        font.setPointSize(12);
        result->setFont(font);
        label = new QLabel(result);
        label->setObjectName("label");
        label->setGeometry(QRect(410, 10, 171, 41));
        QFont font1;
        font1.setPointSize(22);
        font1.setBold(true);
        label->setFont(font1);
        scrollArea = new QScrollArea(result);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(30, 70, 921, 591));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 919, 589));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label_2 = new QLabel(result);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 680, 921, 71));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(true);
        label_2->setFont(font2);

        retranslateUi(result);

        QMetaObject::connectSlotsByName(result);
    } // setupUi

    void retranslateUi(QDialog *result)
    {
        result->setWindowTitle(QCoreApplication::translate("result", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("result", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class result: public Ui_result {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULT_H
