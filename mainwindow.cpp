#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <chrono>
#include <iostream>
#include <QtSerialPort>
#include <QGraphicsOpacityEffect>
#include <QDebug>

QSerialPort *serial;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *label = ui->label;
    label->setText("<--[-------]-->");
    label->setStyleSheet("QLabel { color : white; }");
    label->setGeometry((this->width() - label->width())/2,
                       (this->height() - label->height())/2,
                       label->width(), label->height());

    QPixmap bkgnd(":/resources/images/background2.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    serial = new QSerialPort(this);
    serial->setPortName("/dev/pts/2");
    serial->setBaudRate(QSerialPort::Baud19200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    serial->write("ok*");
    qDebug() << "serial opened";
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
}

void MainWindow::setText(const QString text) {
    ui->label->setText(text);
}

void MainWindow::serialReceived() {
    QByteArray ba;
    ba = serial->readAll();
    ui->label->setText(ba);
    qDebug() << "test" << ba;
}

