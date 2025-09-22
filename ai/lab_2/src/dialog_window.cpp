#include "dialog_window.h"
#include "log/log.h"

#include <QMessageBox>

DialogWindow::DialogWindow()
{
    this->setMinimumSize(200, 120);
    this->setMaximumSize(200, 120);
    this->setWindowTitle("Введите размер лабиринта");

    maze_size_text_edit      = new TextEdit("0", this);
    ok                       = new Button([&](){click_ok_button();}, this, "OK");

    maze_size_text_edit->setGeometry(5, 5, 190, 50);
    ok->setGeometry(5, 60, 190, 50);
}

DialogWindow::~DialogWindow()
{
    ;
}

void DialogWindow::click_ok_button()
{
    bool ok;
    
    int number = maze_size_text_edit->get_text().toInt(&ok);

    if (number < 5)
    {
        QMessageBox::warning(nullptr, "Ошибка", "Поле доджно иметь размер больше или равно(5x5)");

        return;
    }

    if (ok) 
    {
        maze_size = number;
        accept();
    } 
    else 
    {
        LogWithError("Недопустимые символы");
    }
}

int DialogWindow::get_maze_size()
{
    return maze_size;
}