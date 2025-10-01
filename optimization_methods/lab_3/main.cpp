#include "processor.h"
#include "cryptographer.h"

#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QProcess>
#include <QString>

int main(int argc, char** argv) 
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Processor process_helper(nullptr);
    
    engine.rootContext()->setContextProperty("process_helper", &process_helper);
    engine.load(QUrl::fromLocalFile(QDir::currentPath() + "/ui.qml"));
    
    return app.exec();
}