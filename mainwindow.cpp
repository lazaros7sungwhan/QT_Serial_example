#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QTimer>
#include <stdio.h>

void scan_serial_port(Ui::MainWindow *ui);
QSerialPort *serial;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    my_timer=new QTimer(this);
    connect(my_timer,SIGNAL(timeout()),this,SLOT(read_data_1()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(connect_serial()));

    //combobox -> serial info
    ui->comboBox->clear();
    foreach(const QSerialPortInfo &serialPortInfo,QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(serialPortInfo.portName());
    }
}
void MainWindow::on_pushButton_clicked()
{
//connect_serial();
}
void MainWindow::on_pushButton_2_clicked()
{
my_timer->stop();
serial->close();
}
void MainWindow::on_pushButton_3_clicked()
{
    Serial_rescan();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Serial_rescan()
{
    qDebug()<<"Serial channel rescanned..";
    ui->comboBox->clear();
    foreach(const QSerialPortInfo &serialPortInfo,QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(serialPortInfo.portName());
    }
}

void MainWindow::read_data_1()
{
   QString received;
   //double number;
   while(serial->canReadLine())
   {
       received=serial->readAll();
   }
   if(received!=NULL)
   //ui->textEdit->setText(received);
ui->lcdNumber->display(received);
}
void MainWindow::connect_serial()
{

    serial->setPortName(ui->comboBox->currentText());
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!serial->open(QIODevice::ReadWrite))
    {
        qDebug()<<"Serial port open error";
    }
    my_timer->start(10);

}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}



