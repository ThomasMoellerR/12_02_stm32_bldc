/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QSpinBox *spinBox_PWM;
    QCheckBox *checkBox;
    QLabel *label;
    QSpinBox *spinBox_TIME;
    QLabel *label_2;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QPushButton *pushButton;
    QLineEdit *lineEdit_SetHall;
    QPushButton *pushButton_SetHall;
    QComboBox *comboBox_Motortyp;
    QLabel *label_4;
    QPushButton *pushButton_Set_Motortyp;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton_Save;
    QLabel *label_10;
    QLabel *label_11;
    QFrame *line;
    QPushButton *pushButton_Set_Mode;
    QLabel *label_6;
    QLineEdit *lineEdit_UMIN;
    QLabel *label_13;
    QLabel *label_9;
    QLineEdit *lineEdit_SetState;
    QPushButton *pushButton_Get_State;
    QLabel *label_12;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(981, 783);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        spinBox_PWM = new QSpinBox(centralWidget);
        spinBox_PWM->setObjectName(QStringLiteral("spinBox_PWM"));
        spinBox_PWM->setGeometry(QRect(270, 290, 61, 22));
        spinBox_PWM->setMaximum(4000);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(360, 310, 70, 17));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 290, 47, 21));
        spinBox_TIME = new QSpinBox(centralWidget);
        spinBox_TIME->setObjectName(QStringLiteral("spinBox_TIME"));
        spinBox_TIME->setGeometry(QRect(80, 480, 61, 22));
        spinBox_TIME->setMaximum(4000);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 459, 161, 16));
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(200, 230, 131, 22));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(210, 520, 113, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 520, 81, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(360, 520, 75, 23));
        lineEdit_SetHall = new QLineEdit(centralWidget);
        lineEdit_SetHall->setObjectName(QStringLiteral("lineEdit_SetHall"));
        lineEdit_SetHall->setGeometry(QRect(200, 150, 113, 20));
        pushButton_SetHall = new QPushButton(centralWidget);
        pushButton_SetHall->setObjectName(QStringLiteral("pushButton_SetHall"));
        pushButton_SetHall->setGeometry(QRect(370, 150, 75, 23));
        comboBox_Motortyp = new QComboBox(centralWidget);
        comboBox_Motortyp->addItem(QString());
        comboBox_Motortyp->addItem(QString());
        comboBox_Motortyp->setObjectName(QStringLiteral("comboBox_Motortyp"));
        comboBox_Motortyp->setGeometry(QRect(200, 70, 151, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(70, 70, 81, 16));
        pushButton_Set_Motortyp = new QPushButton(centralWidget);
        pushButton_Set_Motortyp->setObjectName(QStringLiteral("pushButton_Set_Motortyp"));
        pushButton_Set_Motortyp->setGeometry(QRect(370, 70, 75, 23));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(70, 150, 111, 16));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(480, 150, 161, 16));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(480, 170, 161, 16));
        pushButton_Save = new QPushButton(centralWidget);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(470, 520, 91, 23));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(220, 440, 331, 16));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(70, 230, 47, 13));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(60, 410, 601, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_Set_Mode = new QPushButton(centralWidget);
        pushButton_Set_Mode->setObjectName(QStringLiteral("pushButton_Set_Mode"));
        pushButton_Set_Mode->setGeometry(QRect(370, 230, 75, 23));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(80, 290, 111, 20));
        lineEdit_UMIN = new QLineEdit(centralWidget);
        lineEdit_UMIN->setObjectName(QStringLiteral("lineEdit_UMIN"));
        lineEdit_UMIN->setGeometry(QRect(220, 370, 113, 20));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(80, 370, 111, 20));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(70, 30, 201, 16));
        lineEdit_SetState = new QLineEdit(centralWidget);
        lineEdit_SetState->setObjectName(QStringLiteral("lineEdit_SetState"));
        lineEdit_SetState->setGeometry(QRect(690, 70, 113, 20));
        pushButton_Get_State = new QPushButton(centralWidget);
        pushButton_Get_State->setObjectName(QStringLiteral("pushButton_Get_State"));
        pushButton_Get_State->setGeometry(QRect(860, 70, 75, 23));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(560, 70, 111, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 981, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Direction", nullptr));
        label->setText(QApplication::translate("MainWindow", "(PWM)", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Kommutierung Zeit", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Steuerung", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Manuelle Kommutierung", nullptr));

        label_3->setText(QApplication::translate("MainWindow", "Hall Detection", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Carry", nullptr));
        pushButton_SetHall->setText(QApplication::translate("MainWindow", "Set", nullptr));
        comboBox_Motortyp->setItemText(0, QApplication::translate("MainWindow", "Hall", nullptr));
        comboBox_Motortyp->setItemText(1, QApplication::translate("MainWindow", "Sensorless", nullptr));

        label_4->setText(QApplication::translate("MainWindow", "1. Set Motortyp", nullptr));
        pushButton_Set_Motortyp->setText(QApplication::translate("MainWindow", "Set", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "2. Set Hall Information", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Roter Motor: 621453", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "CD Laufwerk: 312546", nullptr));
        pushButton_Save->setText(QApplication::translate("MainWindow", "Save in Config", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Manuelle Kommutierung und Hall Erkennung", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "3. Modus", nullptr));
        pushButton_Set_Mode->setText(QApplication::translate("MainWindow", "Set", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Steuerung / Man Kom", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Get U/Sek", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "C:/Json_Files/BLCD_Testsoftware.json", nullptr));
        lineEdit_SetState->setText(QString());
        pushButton_Get_State->setText(QApplication::translate("MainWindow", "Read", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Get State", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
