#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QtSql>
#include <iostream>
#include <QSqlTableModel>
#include <QString>

using namespace std;

const static QString QueryLoadAllValues = "SELECT tblvalue.intTemperature, tblvalue.intHumidity, tblvalue.intPressure "
                                          "FROM tblValue ORDER BY tblvalue.ID DESC LIMIT 1;";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connection with database
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("databases.aii.avans.nl");
    db.setPort(3306);
    db.setUserName("dallegie");
    db.setPassword("Ab12345");
    db.setDatabaseName("dallegie_db");

    if(db.open()){
        qDebug() << "DB connected";

        QSqlQuery queryTest;
        queryTest.prepare(QueryLoadAllValues); //Query prepared for use

        if(queryTest.exec()){ //Execution of the query
            queryTest.first();

            if(temperature){
                ui->lcdTemperature->display((queryTest.value(0).toInt()/10));           // Shows degrees
            }else{
                 ui->lcdTemperature->display((queryTest.value(0).toInt()/10 * 1.8 + 32));// Shows fahrenheit
            }

            ui->lcdAirHumidity->display(queryTest.value(1).toInt());               // Shows airHumidity
            ui->lcdAirPressure->display(queryTest.value(2).toInt());                      // Shows airPressure
        }

        modType = new QSqlQueryModel(); //Create new Model

        queryTest.prepare("Select tbldateandtime.ID, tbldateandtime.dateDate, tbldateandtime.timeTime from tbldateandtime order by ID DESC;"); //Second query
        if(queryTest.exec()){
            modType->clear(); //Clear the data in the modType
            modType->setQuery(queryTest); //Set the new query in the modType
            ui->Date->setModel(modType);
            ui->Date->resizeColumnsToContents();
         }

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
}

void MainWindow::on_Date_clicked(const QModelIndex &index)
{
    QSqlQuery queryTest; //Set new query

    QVariant data = index.data(); //The variant contains an index that is given

    modType = new QSqlQueryModel; //Create new Model

    idString = data.toString(); //convert Data to a string

    queryTest.prepare("SELECT tbldateandtime.ID From tbldateandtime WHERE tbldateandtime.ID = '"+idString+"' ORDER BY tbldateandtime.ID DESC;"); //Query prepared for use
    if(queryTest.exec()){ //Execution of the query
        queryTest.first();
    }

    queryTest.prepare("SELECT tblvalue.intTemperature, tblvalue.intHumidity, tblvalue.intPressure FROM tblValue WHERE tblvalue.ID = '"+idString+"' ORDER BY tblvalue.ID DESC LIMIT 1;"); //Query prepared for use
    if(queryTest.exec()){ //Execution of the query
        queryTest.first();
        if(temperature){
            ui->lcdTemperature->display((queryTest.value(0).toInt()/10));           // Shows degrees
        }else{
             ui->lcdTemperature->display((queryTest.value(0).toInt()/10 * 1.8 + 32));//Fahrenheit
        }
        ui->lcdAirHumidity->display(queryTest.value(1).toInt());
        ui->lcdAirPressure->display(queryTest.value(2).toInt());
    }

}

void MainWindow::on_Degrees_clicked()
{
    temperature = 1;                                                                // Set temperature as degrees
    ui->Degrees->setChecked(1);                                                      // Updates radiobuttons
    ui->Fahrenheit->setChecked(0);
    updateTemperature();                                                            // Updates Temperature
}

void MainWindow::on_Fahrenheit_clicked()
{
    temperature = 0;                                                                // Set temperature as fahrenheit
    ui->Degrees->setChecked(0);                                                      // Updates radiobuttons
    ui->Fahrenheit->setChecked(1);
    updateTemperature();                                                            // Updates Temperature
}

void MainWindow::updateTemperature()
{
    QSqlQuery queryTest;                                                             // Set new query
    if( idString != "") {                                                            // Checks if there was a selection in the tablevieuw
        queryTest.prepare("SELECT tblvalue.intTemperature FROM tblValue WHERE tblvalue.ID = '"+idString+"' ORDER BY tblvalue.ID DESC LIMIT 1;"); //Query prepared for use
    } else {
        queryTest.prepare("SELECT tblvalue.intTemperature FROM tblValue ORDER BY tblvalue.ID DESC LIMIT 1;");
    }
    if(queryTest.exec()){                                                            //Execution of the query
         queryTest.first();
        if(temperature){
            ui->lcdTemperature->display((queryTest.value(0).toInt()/10));            //Degrees
        }else{
            ui->lcdTemperature->display((queryTest.value(0).toInt()/10 * 1.8 + 32)); // Shows fahrenheit
        }
    }
}
