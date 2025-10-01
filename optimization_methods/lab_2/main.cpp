#include "processor.h"
#include "cryptographer.h"

#include <ctime>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QProcess>
#include <QString>


int main(int argc, char** argv) 
{
    std::srand(std::time(0));

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Processor process_helper(nullptr);
    
    engine.rootContext()->setContextProperty("process_helper", &process_helper);
    engine.load(QUrl::fromLocalFile(QDir::currentPath() + "/ui.qml"));
    
    return app.exec();
}