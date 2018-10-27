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

#define LOAD_ALL_MEASUMENTS_DAYS_TIMES "SELECT tbldateandtime.ID, "\
                                       "DATE_FORMAT(tbldateandtime.dateDate,\"%d-%m-%Y\") AS `Date`, "\
                                       "TIME_FORMAT(tbldateandtime.timeTime,\"%h:%i:%s\") AS \"Time\" "\
                                       "FROM tbldateandtime "\
                                       "ORDER BY tbldateandtime.dateDate DESC, tbldateandtime.timeTime DESC "

#define LOAD_VALUES_FROM_DATETIME "SELECT tblvalue.intTemperature AS TEMP, tblvalue.intHumidity AS HUMID, tblvalue.intPressure AS PRESS "\
                                  "FROM tbldateandtime "\
                                  "INNER JOIN tbldateandtimevalue ON tbldateandtime.ID = tbldateandtimevalue.TimeID "\
                                  "INNER JOIN tblvalue ON tbldateandtimevalue.ValueID = tblvalue.ID "\
                                  "WHERE tbldateandtime.ID = "


#define TEMPERATURE static_cast<int>(0)
#define HUMIDITY static_cast<int>(1)
#define PRESSURE static_cast<int>(2)
#define DATE static_cast<int>(1)
#define TIME static_cast<int>(2)

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

private:
    QSqlDatabase db;
    Ui::MainWindow *ui;
    QSqlQueryModel *queryModel;
    bool isTempCelsius = true; // false is for fahrenheit
    bool isAValueSelected = false;

    struct measurement currentSelectedMeasurement;

    void set_database();
    void update_text_boxes();
};

#endif // MAINWINDOW_H
