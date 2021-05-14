#include "ttext.h"
#include <chrono>
#include <iostream>

ttext::ttext(QObject *parent):
    serial_stop(false)
{
    (void)parent;

    text = "";

    ptr_serial = new QSerialPort();
    ptr_serial->setPortName("/dev/pts/2");
    ptr_serial->setDataBits(QSerialPort::Data8);
    ptr_serial->setBaudRate(QSerialPort::Baud19200);
    ptr_serial->setStopBits(QSerialPort::OneStop);
    ptr_serial->setParity(QSerialPort::NoParity);
    ptr_serial->setFlowControl(QSerialPort::NoFlowControl);
    ptr_serial->open(QIODevice::ReadWrite);
    ptr_serial->write("ok*");
    qDebug() << "serial opened";
    QObject::connect(ptr_serial, SIGNAL(readyRead()), this, SLOT(serialReceived()));

    test_loop = std::thread([&]() {
        using namespace std::chrono;
        auto ts = system_clock::now();
        bool active = false;
        while(!serial_stop) {
            auto time_passed = duration_cast<milliseconds>(system_clock::now() - ts).count();
            if (time_passed > 999) {
                ts = system_clock::now();
                active = !active;
                if (active) this->setText(">--|||||||||--<");
                else        this->setText("<--[-------]-->");
            }
            std::this_thread::sleep_for(milliseconds(100));
        }
    });
}

ttext::~ttext()
{
    ptr_serial->close();
    delete ptr_serial;
    serial_stop = true;
    test_loop.join();
    std::cout << "App has finished" << std::endl;
}

void ttext::setText(const QString &text) {
    this->text = text;
    emit textChanged(text);
}

QString& ttext::getText() {
    return this->text;
}

void ttext::serialReceived() {
    QByteArray ba;
    ba = ptr_serial->readAll();
    qDebug() << "test: " << ba;
}
