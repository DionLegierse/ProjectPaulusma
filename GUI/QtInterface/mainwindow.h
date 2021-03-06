#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QDateTimeAxis>

//A macro with the query to load all measurements dates and times from the database
#define LOAD_ALL_MEASUMENTS_DAYS_TIMES "SELECT tbldateandtime.ID, "\
                                       "DATE_FORMAT(tbldateandtime.dateDate,\"%d-%m-%Y\") AS `Date`, "\
                                       "TIME_FORMAT(tbldateandtime.timeTime,\"%H:%i:%s\") AS \"Time\" "\
                                       "FROM tbldateandtime "\
                                       "ORDER BY tbldateandtime.dateDate DESC, tbldateandtime.timeTime DESC "

//A macro with the query to the measurement data from the selected day
#define LOAD_VALUES_FROM_DATETIME "SELECT tblvalue.intTemperature AS TEMP, tblvalue.intHumidity AS HUMID, tblvalue.intPressure AS PRESS "\
                                  "FROM tbldateandtime "\
                                  "INNER JOIN tbldateandtimevalue ON tbldateandtime.ID = tbldateandtimevalue.TimeID "\
                                  "INNER JOIN tblvalue ON tbldateandtimevalue.ValueID = tblvalue.ID "\
                                  "WHERE tbldateandtime.ID = "

//A macro with the query to find all days that measurements have been made on
#define FIND_ALL_DISTINCT_DATES "SELECT DISTINCT DATE_FORMAT(tbldateandtime.dateDate, \"%d-%m-%Y\") AS `date` "\
                                "FROM tbldateandtime "\
                                "ORDER BY `date` DESC"

//A macro with a query to find all temperature measurements on the selected day
#define FIND_ALL_TEMPERATURE_ON_DAY "SELECT DATE_FORMAT(tbldateandtime.dateDate, \"%d-%m-%Y\") AS `date`, "\
                                    "TIME_FORMAT(tbldateandtime.timeTime, \"%H:%i:%s\"), FORMAT(tblvalue.intTemperature/ 10, 1) AS TEMP "\
                                    "FROM tbldateandtime "\
                                    "INNER JOIN tbldateandtimevalue ON tbldateandtime.ID = tbldateandtimevalue.TimeID "\
                                    "INNER JOIN tblvalue ON tbldateandtimevalue.ValueID = tblvalue.ID "\
                                    "HAVING `date` =\""

//A macro with a query to find all humidity measurements on the selected day
#define FIND_ALL_HUMIDITY_ON_DAY "SELECT DATE_FORMAT(tbldateandtime.dateDate, \"%d-%m-%Y\") AS `date`, "\
                                 "TIME_FORMAT(tbldateandtime.timeTime, \"%H:%i:%s\"), FORMAT(tblvalue.intHumidity, 1) AS HUMIDITY "\
                                 "FROM tbldateandtime "\
                                 "INNER JOIN tbldateandtimevalue ON tbldateandtime.ID = tbldateandtimevalue.TimeID "\
                                 "INNER JOIN tblvalue ON tbldateandtimevalue.ValueID = tblvalue.ID "\
                                 "HAVING `date` =\""

//A macro with a query to find all pressure measurements on the selected day
#define FIND_ALL_PRESSURE_ON_DAY "SELECT DATE_FORMAT(tbldateandtime.dateDate, \"%d-%m-%Y\") AS `date`, "\
                                 "TIME_FORMAT(tbldateandtime.timeTime, \"%H:%i:%s\"), tblvalue.intPressure AS PRESSURE "\
                                 "FROM tbldateandtime "\
                                 "INNER JOIN tbldateandtimevalue ON tbldateandtime.ID = tbldateandtimevalue.TimeID "\
                                 "INNER JOIN tblvalue ON tbldateandtimevalue.ValueID = tblvalue.ID "\
                                 "HAVING `date` =\""

#define TEMPERATURE static_cast<int>(0)
#define HUMIDITY static_cast<int>(1)
#define PRESSURE static_cast<int>(2)
#define DATE static_cast<int>(1)
#define TIME static_cast<int>(2)

#define MAIN_WINDOW_CHART_WIDTH static_cast<int>(1218)

struct measurement{
    double temperature;
    int humidity;
    int pressure;
    QString date;
    QString time;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_tvDatesTimes_clicked(const QModelIndex &index);

    void on_rbCelsius_toggled(bool checked);

    void on_rbFahrenheit_toggled(bool checked);

    void on_pbGenerateChart_pressed();

private:
    QSqlDatabase db;

    bool isTempCelsius = true; // false is for fahrenheit
    bool isAValueSelected = false;
    bool isChartPointersSet = false;

    struct measurement currentSelectedMeasurement;

    Ui::MainWindow *ui = nullptr;
    QSqlQueryModel *queryModel = nullptr;
    QtCharts::QLineSeries * measurementSeries = nullptr;
    QtCharts::QChart * lineChart = nullptr;
    QtCharts::QChartView * chartView = nullptr;
    QtCharts::QDateTimeAxis * xAxisDateTime = nullptr;
    QtCharts::QValueAxis * yAxisValues = nullptr;

    void set_database();
    void update_text_boxes();
    void init_tableview_date_time();
    void init_cmbDates();
    void fill_chart_values(QSqlQuery& querye);
    void check_if_chart_is_set();
    void initialize_chart();
    void set_correct_y_format();
};

#endif // MAINWINDOW_H
