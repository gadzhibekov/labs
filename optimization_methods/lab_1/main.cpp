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
    // std::cout << "=== Алгоритм с математическими преобразованиями ===" << std::endl;
    
    // Cryptographer::key = 42;
    // std::string originalText = "Hello, World!";
    
    // std::cout << "Исходный текст: " << originalText << std::endl;
    
    // auto encrypted = Cryptographer::encrypt(originalText);
    // std::cout << "Зашифрованные данные: ";
    // for (double val : encrypted) 
    // {
    //     std::cout << val << " ";
    // }
    // std::cout << std::endl;
    
    // std::string decrypted = Cryptographer::decrypt(encrypted);
    // std::cout << "Расшифрованный текст: " << decrypted << std::endl;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Processor process_helper(nullptr);
    
    engine.rootContext()->setContextProperty("process_helper", &process_helper);
    engine.load(QUrl::fromLocalFile(QDir::currentPath() + "/ui.qml"));
    
    return app.exec();
}