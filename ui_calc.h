/********************************************************************************
** Form generated from reading UI file 'calc.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALC_H
#define UI_CALC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CalcDialog
{
public:
    QPushButton *calcbutton;
    QLineEdit *imei;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *flashcode;
    QLineEdit *v1code;
    QLineEdit *v2code;
    QLineEdit *v201code;
    QPushButton *exitbutton;
    QLabel *label_6;
    QFrame *line;

    void setupUi(QDialog *CalcDialog)
    {
        if (CalcDialog->objectName().isEmpty())
            CalcDialog->setObjectName(QString::fromUtf8("CalcDialog"));
        CalcDialog->resize(365, 242);
        QPalette palette;
        QBrush brush(QColor(0, 85, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(141, 138, 136, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        CalcDialog->setPalette(palette);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        CalcDialog->setWindowIcon(icon);
        calcbutton = new QPushButton(CalcDialog);
        calcbutton->setObjectName(QString::fromUtf8("calcbutton"));
        calcbutton->setGeometry(QRect(250, 60, 94, 24));
        calcbutton->setDefault(true);
        imei = new QLineEdit(CalcDialog);
        imei->setObjectName(QString::fromUtf8("imei"));
        imei->setGeometry(QRect(110, 60, 131, 23));
        imei->setMaxLength(15);
        imei->setDragEnabled(true);
        label = new QLabel(CalcDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 60, 51, 20));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label->setPalette(palette1);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(CalcDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 100, 71, 16));
        QPalette palette2;
        QBrush brush3(QColor(0, 0, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_2->setPalette(palette2);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_3 = new QLabel(CalcDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 130, 55, 15));
        label_3->setFont(font1);
        label_4 = new QLabel(CalcDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 160, 55, 15));
        label_4->setFont(font1);
        label_5 = new QLabel(CalcDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(24, 190, 71, 20));
        QPalette palette3;
        QBrush brush4(QColor(0, 170, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_5->setPalette(palette3);
        label_5->setFont(font1);
        flashcode = new QLineEdit(CalcDialog);
        flashcode->setObjectName(QString::fromUtf8("flashcode"));
        flashcode->setGeometry(QRect(110, 100, 101, 23));
        flashcode->setReadOnly(true);
        v1code = new QLineEdit(CalcDialog);
        v1code->setObjectName(QString::fromUtf8("v1code"));
        v1code->setGeometry(QRect(110, 130, 101, 23));
        v1code->setReadOnly(true);
        v2code = new QLineEdit(CalcDialog);
        v2code->setObjectName(QString::fromUtf8("v2code"));
        v2code->setGeometry(QRect(110, 160, 101, 23));
        v2code->setReadOnly(true);
        v201code = new QLineEdit(CalcDialog);
        v201code->setObjectName(QString::fromUtf8("v201code"));
        v201code->setGeometry(QRect(110, 190, 101, 23));
        v201code->setReadOnly(true);
        exitbutton = new QPushButton(CalcDialog);
        exitbutton->setObjectName(QString::fromUtf8("exitbutton"));
        exitbutton->setGeometry(QRect(250, 100, 94, 24));
        label_6 = new QLabel(CalcDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 20, 341, 20));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        label_6->setFont(font2);
        line = new QFrame(CalcDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(-10, 40, 371, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(CalcDialog);
        QObject::connect(calcbutton, SIGNAL(clicked()), CalcDialog, SLOT(calc()));
        QObject::connect(exitbutton, SIGNAL(clicked()), CalcDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(CalcDialog);
    } // setupUi

    void retranslateUi(QDialog *CalcDialog)
    {
        CalcDialog->setWindowTitle(QApplication::translate("CalcDialog", "Huawei calculator", 0, QApplication::UnicodeUTF8));
        calcbutton->setText(QApplication::translate("CalcDialog", "Calc", 0, QApplication::UnicodeUTF8));
        imei->setInputMask(QApplication::translate("CalcDialog", "999999999999999; ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CalcDialog", "IMEI", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CalcDialog", "Flash code", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CalcDialog", "v1 code", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CalcDialog", "v2 code", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("CalcDialog", "v201 code", 0, QApplication::UnicodeUTF8));
        exitbutton->setText(QApplication::translate("CalcDialog", "Exit", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("CalcDialog", "HUAWEI Unlock code calculator", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalcDialog: public Ui_CalcDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALC_H
