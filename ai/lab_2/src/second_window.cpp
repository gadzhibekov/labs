#include "second_window.h"
#include "main_window.h"
#include "log/log.h"
#include "game.h"

#include <QString>
#include <QProcess>
#include <QCoreApplication>

SecondWindow::SecondWindow(int minimum_count_of_solutions, int maximum_count_of_solutions, int short_path)
{
    this->setMinimumSize(200, 140);
    this->setMaximumSize(200, 140);
    this->setWindowTitle("Вспомагательное окно");

    text_inf_1               = new Text("Количество решений: " + QString::number(maximum_count_of_solutions), this);
    text_inf_2               = new Text("Самое короткое решение: " + QString::number(short_path), this);
    min_count_of_solutions   = new Text(QString::number(minimum_count_of_solutions) + "<", this);
    max_count_of_solutions   = new Text("<=" + QString::number(maximum_count_of_solutions), this);
    index_of_solutions       = new TextEdit("0", this);
    ok                       = new Button([&](){click_ok_button();}, this, "OK");
    show_map                 = new Button([&](){click_show_map_button();}, this, "Показать лабиринт");
    restart                  = new Button([&](){click_restart_button();}, this, "Перезапустить");


    text_inf_1->setGeometry(5, 5, 180, 20);
    text_inf_2->setGeometry(5, 30, 180, 20);
    min_count_of_solutions->setGeometry(5, 55, 50, 20);
    index_of_solutions->setGeometry(30, 55, 50, 20);
    max_count_of_solutions->setGeometry(85, 55, 50, 20);
    ok->setGeometry(140, 55, 30, 20);
    show_map->setGeometry(5, 80, 180, 20);
    restart->setGeometry(5, 110, 180, 20);
}

SecondWindow::~SecondWindow()
{
    ;
}

void SecondWindow::click_ok_button()
{    
    bool ok;
    
    int number = index_of_solutions->get_text().toInt(&ok);

    if (ok) 
    {
        if (0 < number && number <= MainWindow::solutions.size())
        {
            MainWindow::draw_path_on_map(MainWindow::solutions[number - 1]);
        }
        else
        {
            LogWithError("Введите число в допустимом диапазоне");    
        }
    } 
    else 
    {
        LogWithError("Недопустимые символы");
    }
}

void SecondWindow::click_restart_button()
{
    QProcess::startDetached(QCoreApplication::applicationFilePath(), QStringList());
    QCoreApplication::quit();
}

void SecondWindow::click_show_map_button()
{
    MainWindow::show_initial_maze(MainWindow::map_2d, MainWindow::size_of_map);
}