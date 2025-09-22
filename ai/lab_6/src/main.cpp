#include "ui.h"
#include "algo.h"

int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    MainWindow MainWindowObject(nullptr);
    MainWindowObject.show();
    return app.exec();
}