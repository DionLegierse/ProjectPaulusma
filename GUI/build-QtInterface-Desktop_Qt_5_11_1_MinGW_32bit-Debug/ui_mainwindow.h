/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableView *Date;
    QLCDNumber *lcdAirPressure;
    QLCDNumber *lcdTemperature;
    QPlainTextEdit *plainTextEdit_3;
    QPlainTextEdit *plainTextEdit;
    QPlainTextEdit *plainTextEdit_2;
    QLCDNumber *lcdAirHumidity;
    QRadioButton *Degrees;
    QRadioButton *Fahrenheit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1099, 861);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Date = new QTableView(centralWidget);
        Date->setObjectName(QStringLiteral("Date"));
        Date->setGeometry(QRect(9, 9, 431, 841));
        lcdAirPressure = new QLCDNumber(centralWidget);
        lcdAirPressure->setObjectName(QStringLiteral("lcdAirPressure"));
        lcdAirPressure->setGeometry(QRect(670, 130, 81, 41));
        lcdAirPressure->setFrameShape(QFrame::Box);
        lcdAirPressure->setProperty("value", QVariant(0));
        lcdTemperature = new QLCDNumber(centralWidget);
        lcdTemperature->setObjectName(QStringLiteral("lcdTemperature"));
        lcdTemperature->setGeometry(QRect(670, 10, 81, 41));
        lcdTemperature->setFrameShape(QFrame::Box);
        lcdTemperature->setProperty("value", QVariant(0));
        plainTextEdit_3 = new QPlainTextEdit(centralWidget);
        plainTextEdit_3->setObjectName(QStringLiteral("plainTextEdit_3"));
        plainTextEdit_3->setGeometry(QRect(460, 130, 211, 41));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(460, 10, 211, 41));
        plainTextEdit_2 = new QPlainTextEdit(centralWidget);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(460, 70, 211, 41));
        lcdAirHumidity = new QLCDNumber(centralWidget);
        lcdAirHumidity->setObjectName(QStringLiteral("lcdAirHumidity"));
        lcdAirHumidity->setGeometry(QRect(670, 70, 81, 41));
        lcdAirHumidity->setFrameShape(QFrame::Box);
        lcdAirHumidity->setProperty("value", QVariant(0));
        Degrees = new QRadioButton(centralWidget);
        Degrees->setObjectName(QStringLiteral("Degrees"));
        Degrees->setGeometry(QRect(770, 20, 141, 20));
        Degrees->setChecked(true);
        Fahrenheit = new QRadioButton(centralWidget);
        Fahrenheit->setObjectName(QStringLiteral("Fahrenheit"));
        Fahrenheit->setGeometry(QRect(880, 20, 151, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1099, 21));
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
        plainTextEdit_3->setPlainText(QApplication::translate("MainWindow", "Air Pressure", nullptr));
        plainTextEdit->setPlainText(QApplication::translate("MainWindow", "Temperature", nullptr));
        plainTextEdit_2->setPlainText(QApplication::translate("MainWindow", "Air Humidity", nullptr));
        Degrees->setText(QApplication::translate("MainWindow", "Graden", nullptr));
        Fahrenheit->setText(QApplication::translate("MainWindow", "Fahrenheit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
