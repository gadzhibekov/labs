#include "main_window.h"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow main_window(nullptr);

    main_window.show();

    return app.exec();
}

/*
    rm -rf * && g++ -fPIC -no-pie ../qt/main.cpp ../qt/main_window.cpp -o app `pkg-config --cflags --libs Qt5Widgets` && ./app 
    rm -rf * && g++ -fPIC -no-pie ../qt/main.cpp ../qt/main_window.cpp ../db.cpp -o app -lsqlite3 `pkg-config --cflags --libs Qt5Widgets` && ./app
    
*/