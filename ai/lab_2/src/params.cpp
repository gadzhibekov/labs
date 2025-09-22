#include "params.h"

ParamsWindow::ParamsWindow(QWidget* parent) : QWidget(parent)
{
        this->setMinimumSize(500, 300);
        this->setMaximumSize(500, 300);

        icon_1          = new Text("", this);
        icon_2          = new Text("", this);
        icon_3          = new Text("", this);
        icon_4          = new Text("", this);

        data_1          = new Text("Зеленый флаг - финиш до которого игрок должен\nдобраться двигась только по зеленым точкам", this);
        data_2          = new Text("Крест - точка старта игрока", this);
        data_3          = new Text("Зеленая точка - путь, где двигаться игрок", this);
        data_4          = new Text("Стера - преграда для игрока игрок не может\nдвигаться через него", this);

        icon_1->setGeometry(0, 0, 50, 50);
        icon_2->setGeometry(0, 50, 50, 50);
        icon_3->setGeometry(0, 150, 50, 50);
        icon_4->setGeometry(0, 200, 50, 50);

        data_1->setGeometry(60, 20, 400, 50);
        data_2->setGeometry(60, 75, 400, 50);
        data_3->setGeometry(60, 150, 400, 50);
        data_4->setGeometry(60, 225, 400, 50);

        icon_1->set_icon("../res/end.png", 50);
        icon_2->set_icon("../res/start.png", 50);
        icon_3->set_icon("../res/h.png", 50);
        icon_4->set_icon("../res/wall.png", 50);

        data_1->set_text_size(13);
        data_2->set_text_size(13);
        data_3->set_text_size(13);
        data_4->set_text_size(13);

        hide_window_button = new Button([&](){hide_widget();}, this, "");
        hide_window_button->setGeometry(500 - 30, 300 - 30, 30, 30);
        hide_window_button->set_icon("../res/close.png", 50);

        this->setStyleSheet("background-color: grey;");

        this->hide();
}

void ParamsWindow::show_widget(int w, int h)
{
        this->setGeometry((w / 2) - 250, (h / 2) - 150, 500, 300);

        this->show();
}

void ParamsWindow::hide_widget()
{
        this->hide();
}