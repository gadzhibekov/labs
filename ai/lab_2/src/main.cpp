#include <QApplication>

#include "main_window.h"
#include "dialog_window.h"
#include "log/log.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    DialogWindow dialog_window;
    dialog_window.exec();

    MainWindow main_window(nullptr, dialog_window.get_maze_size());
    main_window.show();

    return app.exec();
}