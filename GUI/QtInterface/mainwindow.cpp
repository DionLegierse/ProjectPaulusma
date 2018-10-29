#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QtSql>
#include <iostream>
#include <QSqlTableModel>
#include <QString>

//The mainwindows constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setup the connection with the database
    this->set_database();

    //fill the table view with the dates and times for the database
    this->init_tableview_date_time();

    this->init_cmbDates();
}

//Initialize the table with all the measurements from the database
void MainWindow::init_tableview_date_time(){
    if(db.open()){
        qDebug() << "DB connected";

        this->queryModel = new QSqlQueryModel(); //Create new Model

        this->queryModel->clear(); //Clear the data in the modType
        this->queryModel->setQuery(LOAD_ALL_MEASUMENTS_DAYS_TIMES); //Set the new query in the modType
        this->ui->tvDatesTimes->setModel(this->queryModel);
        this->ui->tvDatesTimes->hideColumn(0);
        this->ui->tvDatesTimes->resizeColumnsToContents();


    }else{
        QSqlError err = db.lastError(); //If error occurred, then print Error.
        qDebug() << "Database:  " << err.databaseText();
        qDebug() << "Driver:  " << err.driverText();
        qDebug() << "Text:  " << err.text();
    }
}

//Initialize the combobox with all the dates that have measurements
void MainWindow::init_cmbDates(){
    this->ui->cmbDays->addItem("(select day)");

    QSqlQuery cmbQuery(FIND_ALL_DISTINCT_DATES);
    cmbQuery.exec();

    cmbQuery.first();

    do{
        this->ui->cmbDays->addItem(cmbQuery.value(0).toString());
    }while(cmbQuery.next());
}

//Setup the connection with the database
void MainWindow::set_database(){
    // Connection with database
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("databases.aii.avans.nl");
    this->db.setPort(3306);
    this->db.setUserName("dallegie");
    this->db.setPassword("Ab12345");
    this->db.setDatabaseName("dallegie_db");
}

//The mainwindow deconstructor
MainWindow::~MainWindow()
{
    delete ui;
    delete this->queryModel;
    delete this->measurementSeries;
    delete this->chartView;
    delete this->xAxisDateTime;
    delete this->yAxisValues;
}

//Updates all the text boxes with the information from the selected measurement
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

//Handles the event of a value being selected in the table
//Extracts the needed data from the database and sends it to the
//text boxes with the update_text_boxes() method
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

//Sets the mode of the temperature measurements to degrees celsius
void MainWindow::on_rbCelsius_toggled(bool checked)
{
    if(checked){
        this->isTempCelsius = true;

        if(this->isAValueSelected)
            this->update_text_boxes();
    }

}

//Sets the mode of the temperature measurements to degrees fahrenheit
void MainWindow::on_rbFahrenheit_toggled(bool checked)
{
    if(checked){
        this->isTempCelsius = false;

        if(this->isAValueSelected)
            this->update_text_boxes();
    }
}

//Checks if there already exists a table.
//Deletes it afterwards and creates a new one.
void MainWindow::check_if_chart_is_set(){
    if(!this->isChartPointersSet){
        this->lineChart = new QtCharts::QChart;
        this->measurementSeries = new QtCharts::QLineSeries;
        this->chartView = new QtCharts::QChartView;
        this->xAxisDateTime = new QtCharts::QDateTimeAxis;
        this->yAxisValues = new QtCharts::QValueAxis;

        this->isChartPointersSet = true;
    }else{
        this->ui->chartGrid->removeWidget(this->chartView);

        delete this->lineChart;
        delete this->measurementSeries;
        delete this->chartView;
        delete this->xAxisDateTime;
        delete this->yAxisValues;

        this->lineChart = new QtCharts::QChart;
        this->measurementSeries = new QtCharts::QLineSeries;
        this->chartView = new QtCharts::QChartView;
        this->xAxisDateTime = new QtCharts::QDateTimeAxis;
        this->yAxisValues = new QtCharts::QValueAxis;
    }
}

//Initiliazes the y axis with the correct name and data display format
void MainWindow::set_correct_y_format(){
    if(this->ui->rbTemperature->isChecked()){
        if(this->isTempCelsius){
            this->yAxisValues->setLabelFormat("%.1f");
            this->yAxisValues->setTitleText("Degrees Celsius");
        }else{
            this->yAxisValues->setLabelFormat("%.1f");
            this->yAxisValues->setTitleText("Degrees Fahrenheit");
        }
    }else if(this->ui->rbHumidity->isChecked()){
        this->yAxisValues->setLabelFormat("%.0f\%");
        this->yAxisValues->setTitleText("Humidity");
    }else if(this->ui->rbPressure->isChecked()){
        this->yAxisValues->setLabelFormat("%.0f");
        this->yAxisValues->setTitleText("Pressure in millibar");
    }
}

//Initializes the format of the chart
void MainWindow::initialize_chart(){
    this->lineChart->addSeries(this->measurementSeries);
    this->lineChart->legend()->hide();

    this->xAxisDateTime->setTickCount(10);
    this->xAxisDateTime->setFormat("hh:mm:ss");
    this->xAxisDateTime->setTitleText("Time");
    this->lineChart->addAxis(this->xAxisDateTime, Qt::AlignBottom);
    this->measurementSeries->attachAxis(this->xAxisDateTime);

    this->set_correct_y_format();
    this->lineChart->addAxis(this->yAxisValues, Qt::AlignLeft);
    this->measurementSeries->attachAxis(this->yAxisValues);
}

//Fills the chart with all the measurements of the selected
//Day and measurement type.
void MainWindow::fill_chart_values(QSqlQuery& query){

    this->check_if_chart_is_set();

    query.first();
    this->measurementSeries->clear();
    do{
        QDateTime measurementTime;
        int hour = query.value(1).toString().left(2).toInt();
        int minute = query.value(1).toString().left(5).right(2).toInt();
        int second = query.value(1).toString().right(2).toInt();
        measurementTime.setTime(QTime(hour,minute,second));
        if(!this->isTempCelsius && this->ui->rbTemperature->isChecked())
            this->measurementSeries->append(measurementTime.toMSecsSinceEpoch(),query.value(2).toDouble() * 1.8 + 32);
        else
            this->measurementSeries->append(measurementTime.toMSecsSinceEpoch(),query.value(2).toDouble());
    }while(query.next());

    this->initialize_chart();

    QPen pen(QRgb(0x000000));
    pen.setWidth(1);
    this->measurementSeries->setPen(pen);

    this->chartView->setChart(this->lineChart);
    this->chartView->setRenderHint(QPainter::Antialiasing);
    this->ui->chartGrid->addWidget(this->chartView);
}

//Handles the generation of the chart after the generate linechart button is pressed
void MainWindow::on_pbGenerateChart_pressed()
{

    QSqlQuery getMeasurementQuery;
    if(this->ui->cmbDays->currentText() != "(select day)"){
        if(this->width() != MAIN_WINDOW_CHART_WIDTH)
            this->resize(MAIN_WINDOW_CHART_WIDTH, this->height());

        if(this->ui->rbTemperature->isChecked()){
            getMeasurementQuery.prepare(FIND_ALL_TEMPERATURE_ON_DAY + ui->cmbDays->currentText() + "\"");
        }else if(this->ui->rbHumidity->isChecked()){
            getMeasurementQuery.prepare(FIND_ALL_HUMIDITY_ON_DAY + ui->cmbDays->currentText() + "\"");
        }else if(this->ui->rbPressure->isChecked()){
            getMeasurementQuery.prepare(FIND_ALL_PRESSURE_ON_DAY + ui->cmbDays->currentText() + "\"");
        }

        getMeasurementQuery.exec();
        this->fill_chart_values(getMeasurementQuery);
    }
}














