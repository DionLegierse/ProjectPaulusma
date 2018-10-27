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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
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
    QTableView *tvDatesTimes;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *lblTemperature;
    QLabel *lblPressure;
    QLabel *lblHumidity;
    QLabel *lblDateTime;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *degreeRadioGrid;
    QRadioButton *rbCelsius;
    QRadioButton *rbFahrenheit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(486, 383);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tvDatesTimes = new QTableView(centralWidget);
        tvDatesTimes->setObjectName(QStringLiteral("tvDatesTimes"));
        tvDatesTimes->setGeometry(QRect(9, 9, 231, 311));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(250, 10, 211, 111));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lblTemperature = new QLabel(gridLayoutWidget);
        lblTemperature->setObjectName(QStringLiteral("lblTemperature"));

        gridLayout->addWidget(lblTemperature, 3, 0, 1, 1);

        lblPressure = new QLabel(gridLayoutWidget);
        lblPressure->setObjectName(QStringLiteral("lblPressure"));

        gridLayout->addWidget(lblPressure, 5, 0, 1, 1);

        lblHumidity = new QLabel(gridLayoutWidget);
        lblHumidity->setObjectName(QStringLiteral("lblHumidity"));

        gridLayout->addWidget(lblHumidity, 4, 0, 1, 1);

        lblDateTime = new QLabel(gridLayoutWidget);
        lblDateTime->setObjectName(QStringLiteral("lblDateTime"));

        gridLayout->addWidget(lblDateTime, 2, 0, 1, 1);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(250, 140, 211, 31));
        degreeRadioGrid = new QHBoxLayout(horizontalLayoutWidget);
        degreeRadioGrid->setSpacing(6);
        degreeRadioGrid->setContentsMargins(11, 11, 11, 11);
        degreeRadioGrid->setObjectName(QStringLiteral("degreeRadioGrid"));
        degreeRadioGrid->setContentsMargins(0, 0, 0, 0);
        rbCelsius = new QRadioButton(horizontalLayoutWidget);
        rbCelsius->setObjectName(QStringLiteral("rbCelsius"));
        rbCelsius->setChecked(true);

        degreeRadioGrid->addWidget(rbCelsius);

        rbFahrenheit = new QRadioButton(horizontalLayoutWidget);
        rbFahrenheit->setObjectName(QStringLiteral("rbFahrenheit"));

        degreeRadioGrid->addWidget(rbFahrenheit);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 486, 21));
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
        lblTemperature->setText(QApplication::translate("MainWindow", "Temperature: -", nullptr));
        lblPressure->setText(QApplication::translate("MainWindow", "Pressure: -", nullptr));
        lblHumidity->setText(QApplication::translate("MainWindow", "Humidity: -", nullptr));
        lblDateTime->setText(QApplication::translate("MainWindow", "Date: - Time: -", nullptr));
        rbCelsius->setText(QApplication::translate("MainWindow", "Celsius", nullptr));
        rbFahrenheit->setText(QApplication::translate("MainWindow", "Fahrenheit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
