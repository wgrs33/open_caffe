#ifndef TTEXT_H
#define TTEXT_H

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QSerialPort>
#include <thread>

class ttext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)

public:
    explicit ttext(QObject *parent = nullptr);
    ~ttext();
    void setText(const QString &text);
    QString& getText();

signals:
    void textChanged(const QString &newText);

private slots:
    void serialReceived();

private:
    QString text;
    QSerialPort *ptr_serial;
    std::thread test_loop;
    bool serial_stop;
};

#endif // TTEXT_H
