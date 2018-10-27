#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QtSql>
#include <iostream>
#include <QSqlTableModel>
#include <QString>

void MainWindow::set_database(){
    // Connection with database
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("databases.aii.avans.nl");
    this->db.setPort(3306);
    this->db.setUserName("dallegie");
    this->db.setPassword("Ab12345");
    this->db.setDatabaseName("dallegie_db");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setup the connection with the database
    this->set_database();

    if(db.open()){
        qDebug() << "DB connected";

        this->queryModel = new QSqlQueryModel(); //Create new Model

        this->queryModel->clear(); //Clear the data in the modType
        this->queryModel->setQuery(LOAD_ALL_MEASUMENTS_DAYS_TIMES); //Set the new query in the modType
        ui->tvDatesTimes->setModel(this->queryModel);
        ui->tvDatesTimes->hideColumn(0);
        ui->tvDatesTimes->resizeColumnsToContents();


    }else{
        QSqlError err = db.lastError(); //If error occurred, then print Error.
        qDebug() << "Database:  " << err.databaseText();
        qDebug() << "Driver:  " << err.driverText();
        qDebug() << "Text:  " << err.text();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->queryModel;

}

void MainWindow::update_text_boxes()
{
    QString temp;

    temp = "Date: " + this->currentSelectedMeasurement.date + " Time: " + this->currentSelectedMeasurement.time;
    ui->lblDateTime->setText(temp);

    if(this->isTempCelsius)
        temp =  "Temperature: "
                + QString::number(this->currentSelectedMeasurement.temperature / 10, 'd', 1)
                + " degrees Celsius"; //create string for temperature measurement in celsius
    else
        temp = "Temperature: "
               + QString::number(((this->currentSelectedMeasurement.temperature / 10) * 1.8) + 32, 'd', 1)
               + " degrees Fahrenheit"; //create string for temperature measurement in fahrenheit

    this->ui->lblTemperature->setText(temp);

    temp = "Humidity: "
           + QString::number(this->currentSelectedMeasurement.humidity)
           + "%"; //create string for humidity measurement in %

    this->ui->lblHumidity->setText(temp);

    temp = "Pressure: "
           + QString::number(this->currentSelectedMeasurement.pressure)
           + " millibar"; //create string for pressure measurement in mBar

    this->ui->lblPressure->setText(temp);
}

void MainWindow::on_tvDatesTimes_clicked(const QModelIndex &index)
{
    this->isAValueSelected = true;
    auto row = index.row();
    this->ui->tvDatesTimes->selectRow(row);

    QString queryString = LOAD_VALUES_FROM_DATETIME; //set the query for getting temperature, humidity, pressure
    queryString += this->ui->tvDatesTimes->model()->index(row,0).data().toString(); //append the ID of the measurement to get to the string
    QSqlQuery query(queryString);

    query.exec();
    query.first();//select the first record

    //store the current measurement information to make it easier to edit the data later
    this->currentSelectedMeasurement.temperature = query.value(TEMPERATURE).toDouble();
    this->currentSelectedMeasurement.humidity = query.value(HUMIDITY).toInt();
    this->currentSelectedMeasurement.pressure = query.value(PRESSURE).toInt();
    this->currentSelectedMeasurement.date = this->ui->tvDatesTimes->model()->index(row,DATE).data().toString();
    this->currentSelectedMeasurement.time = this->ui->tvDatesTimes->model()->index(row,TIME).data().toString();

    this->update_text_boxes();
}

void MainWindow::on_rbCelsius_toggled(bool checked)
{
    if(checked){
        this->isTempCelsius = true;

        if(this->isAValueSelected)
            this->update_text_boxes();
    }

}

void MainWindow::on_rbFahrenheit_toggled(bool checked)
{
    if(checked){
        this->isTempCelsius = false;

        if(this->isAValueSelected)
            this->update_text_boxes();
    }
}
