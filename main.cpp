#include "mainwindow.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <QDebug>

#include <QApplication>

//int main(int argc, char *argv[])
//{
//    qSetMessagePattern("[%{type}] %{appname} (%{file}:%{line}) - %{message}");
//    QApplication qapp(argc, argv);
//    MainWindow w;
//    w.setFixedSize(800, 480);
//    bool serial_stop = false;
//    std::thread test_loop ([&]() {
//        using namespace std::chrono;
//        auto ts = system_clock::now();
//        bool active = false;
//        while(!serial_stop) {
//            auto time_passed = duration_cast<milliseconds>(system_clock::now() - ts).count();
//            if (time_passed > 999) {
//                ts = system_clock::now();
//                active = !active;
//                if (active) w.setText(">--|||||||||--<");
//                else        w.setText("<--[-------]-->");
//            }
//            std::this_thread::sleep_for(milliseconds(100));
//        }
//    });
//    w.show();
//    qapp.exec();

//    serial_stop = true;
//    test_loop.join();
//    std::cout << "App has finished" << std::endl;
//    return 0;
//}

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/gui.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
