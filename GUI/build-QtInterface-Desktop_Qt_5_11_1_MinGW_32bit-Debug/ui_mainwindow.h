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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QGridLayout *gridMeasurementInfo;
    QLabel *lblTemperature;
    QLabel *lblPressure;
    QLabel *lblHumidity;
    QLabel *lblDateTime;
    QHBoxLayout *degreeRadioGrid;
    QRadioButton *rbCelsius;
    QRadioButton *rbFahrenheit;
    QWidget *gridLayoutWidget_2;
    QGridLayout *chartOptionsGrid;
    QComboBox *cmbDays;
    QPushButton *pbGenerateChart;
    QLabel *lblChartOptions;
    QRadioButton *rbTemperature;
    QRadioButton *rbHumidity;
    QRadioButton *rbPressure;
    QWidget *gridLayoutWidget_3;
    QGridLayout *chartGrid;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(936, 359);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tvDatesTimes = new QTableView(centralWidget);
        tvDatesTimes->setObjectName(QStringLiteral("tvDatesTimes"));
        tvDatesTimes->setGeometry(QRect(9, 9, 181, 291));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(200, 10, 211, 141));
        gridMeasurementInfo = new QGridLayout(gridLayoutWidget);
        gridMeasurementInfo->setSpacing(6);
        gridMeasurementInfo->setContentsMargins(11, 11, 11, 11);
        gridMeasurementInfo->setObjectName(QStringLiteral("gridMeasurementInfo"));
        gridMeasurementInfo->setContentsMargins(0, 0, 0, 0);
        lblTemperature = new QLabel(gridLayoutWidget);
        lblTemperature->setObjectName(QStringLiteral("lblTemperature"));

        gridMeasurementInfo->addWidget(lblTemperature, 3, 0, 1, 1);

        lblPressure = new QLabel(gridLayoutWidget);
        lblPressure->setObjectName(QStringLiteral("lblPressure"));

        gridMeasurementInfo->addWidget(lblPressure, 5, 0, 1, 1);

        lblHumidity = new QLabel(gridLayoutWidget);
        lblHumidity->setObjectName(QStringLiteral("lblHumidity"));

        gridMeasurementInfo->addWidget(lblHumidity, 4, 0, 1, 1);

        lblDateTime = new QLabel(gridLayoutWidget);
        lblDateTime->setObjectName(QStringLiteral("lblDateTime"));

        gridMeasurementInfo->addWidget(lblDateTime, 2, 0, 1, 1);

        degreeRadioGrid = new QHBoxLayout();
        degreeRadioGrid->setSpacing(6);
        degreeRadioGrid->setObjectName(QStringLiteral("degreeRadioGrid"));
        rbCelsius = new QRadioButton(gridLayoutWidget);
        rbCelsius->setObjectName(QStringLiteral("rbCelsius"));
        rbCelsius->setChecked(true);

        degreeRadioGrid->addWidget(rbCelsius);

        rbFahrenheit = new QRadioButton(gridLayoutWidget);
        rbFahrenheit->setObjectName(QStringLiteral("rbFahrenheit"));

        degreeRadioGrid->addWidget(rbFahrenheit);


        gridMeasurementInfo->addLayout(degreeRadioGrid, 6, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(200, 150, 211, 151));
        chartOptionsGrid = new QGridLayout(gridLayoutWidget_2);
        chartOptionsGrid->setSpacing(6);
        chartOptionsGrid->setContentsMargins(11, 11, 11, 11);
        chartOptionsGrid->setObjectName(QStringLiteral("chartOptionsGrid"));
        chartOptionsGrid->setContentsMargins(0, 0, 0, 0);
        cmbDays = new QComboBox(gridLayoutWidget_2);
        cmbDays->setObjectName(QStringLiteral("cmbDays"));

        chartOptionsGrid->addWidget(cmbDays, 4, 0, 1, 1);

        pbGenerateChart = new QPushButton(gridLayoutWidget_2);
        pbGenerateChart->setObjectName(QStringLiteral("pbGenerateChart"));

        chartOptionsGrid->addWidget(pbGenerateChart, 5, 0, 1, 1);

        lblChartOptions = new QLabel(gridLayoutWidget_2);
        lblChartOptions->setObjectName(QStringLiteral("lblChartOptions"));

        chartOptionsGrid->addWidget(lblChartOptions, 0, 0, 1, 1);

        rbTemperature = new QRadioButton(gridLayoutWidget_2);
        rbTemperature->setObjectName(QStringLiteral("rbTemperature"));

        chartOptionsGrid->addWidget(rbTemperature, 1, 0, 1, 1);

        rbHumidity = new QRadioButton(gridLayoutWidget_2);
        rbHumidity->setObjectName(QStringLiteral("rbHumidity"));

        chartOptionsGrid->addWidget(rbHumidity, 2, 0, 1, 1);

        rbPressure = new QRadioButton(gridLayoutWidget_2);
        rbPressure->setObjectName(QStringLiteral("rbPressure"));

        chartOptionsGrid->addWidget(rbPressure, 3, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralWidget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(420, 10, 511, 291));
        chartGrid = new QGridLayout(gridLayoutWidget_3);
        chartGrid->setSpacing(6);
        chartGrid->setContentsMargins(11, 11, 11, 11);
        chartGrid->setObjectName(QStringLiteral("chartGrid"));
        chartGrid->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 936, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Baulusma weather app", nullptr));
        lblTemperature->setText(QApplication::translate("MainWindow", "Temperature: -", nullptr));
        lblPressure->setText(QApplication::translate("MainWindow", "Pressure: -", nullptr));
        lblHumidity->setText(QApplication::translate("MainWindow", "Humidity: -", nullptr));
        lblDateTime->setText(QApplication::translate("MainWindow", "Date: - Time: -", nullptr));
        rbCelsius->setText(QApplication::translate("MainWindow", "Celsius", nullptr));
        rbFahrenheit->setText(QApplication::translate("MainWindow", "Fahrenheit", nullptr));
        pbGenerateChart->setText(QApplication::translate("MainWindow", "Generate linechart", nullptr));
        lblChartOptions->setText(QApplication::translate("MainWindow", "Chart options:", nullptr));
        rbTemperature->setText(QApplication::translate("MainWindow", "Temperature", nullptr));
        rbHumidity->setText(QApplication::translate("MainWindow", "Humidity", nullptr));
        rbPressure->setText(QApplication::translate("MainWindow", "Pressure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
