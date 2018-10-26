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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateTemperature();

private slots:

    void on_Date_clicked(const QModelIndex &index);

    void on_Degrees_clicked();

    void on_Fahrenheit_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *modType;
    QString idString;  //String to search the previous query
    bool temperature = true; // 1 for degrees and 0 for fahrenheit
};

#endif // MAINWINDOW_H
