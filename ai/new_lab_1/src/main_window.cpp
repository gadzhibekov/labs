#include "main_window.h"
#include "game.h"

#include <QString>
#include <QPalette>
#include <QPixmap>

#include <iostream>
#include <cmath>

FBVector            MainWindow::chess_field_items;
QLabel*             MainWindow::results;
std::vector<int>    MainWindow::positions;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    central_widget = new QWidget(this);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::gray);
    this->setPalette(palette);

    this->setCentralWidget(central_widget);
    this->setMinimumSize(800, 800);
    this->setMaximumSize(800, 800);
    this->setWindowTitle("Лаба1 (Виноградов Алексей)");

    QPixmap pixmap_bk(BLACK_KING_PATH);
    QPixmap pixmap_wk(WHITE_KING_PATH);
    QPixmap pixmap_wr(WHITE_ROOK_PATH);

    bk_icon = new QLabel(central_widget);
    bk_icon->setPixmap(pixmap_bk);
    bk_icon->setGeometry(FIELD_BUTTON_SIZE * 10, FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE);

    bk_text = new QLabel(" - 1 (Черный король)", central_widget);
    bk_text->setStyleSheet("font-size: 30px;");
    bk_text->setGeometry(60 + FIELD_BUTTON_SIZE * 10, FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE * 4, FIELD_BUTTON_SIZE);

    wk_icon = new QLabel(central_widget);
    wk_icon->setPixmap(pixmap_wk);
    wk_icon->setGeometry(FIELD_BUTTON_SIZE * 10, FIELD_BUTTON_SIZE * 2, FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE);

    wk_text = new QLabel(" - 1 (Белый король)", central_widget);
    wk_text->setStyleSheet("font-size: 30px;");
    wk_text->setGeometry(60 + FIELD_BUTTON_SIZE * 10, FIELD_BUTTON_SIZE * 2, FIELD_BUTTON_SIZE * 4, FIELD_BUTTON_SIZE);

    wr_icon = new QLabel(central_widget);
    wr_icon->setPixmap(pixmap_wr);
    wr_icon->setGeometry(5 + FIELD_BUTTON_SIZE * 10, FIELD_BUTTON_SIZE * 3, FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE);

    wr_text = new QLabel(" - 2 (Ладья)", central_widget);
    wr_text->setStyleSheet("font-size: 30px;");
    wr_text->setGeometry(60 + FIELD_BUTTON_SIZE * 10, FIELD_BUTTON_SIZE * 3, FIELD_BUTTON_SIZE * 4, FIELD_BUTTON_SIZE);

    results = new QLabel(central_widget);
    results->setStyleSheet("font-size: 20px;");
    results->setGeometry(FIELD_BUTTON_SIZE * 10, FIELD_BUTTON_SIZE * 5, 1300 - (FIELD_BUTTON_SIZE * 10), FIELD_BUTTON_SIZE);

    positions = random_numbers();

    generate_field(FIELD_SIZE);
    generate_players(positions[0], positions[1], positions[2], positions[3]);
}

void MainWindow::generate_field(int size)
{
    bool swap = true;

    for (int i = 0, id = 1, row = 1, column = 1; i < size ; ++i, id++)
    {
        chess_field_items.push_back(new FieldButton(central_widget, id, {column, row}));
        chess_field_items[i]->setGeometry(row * FIELD_BUTTON_SIZE, column * FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE);
        
        if (swap)
        {
            if (i % 2 == 0)         chess_field_items[i]->set_color(200, 200, 200);
            else                    chess_field_items[i]->set_color(50, 50, 50);
        }
        else
        {
            if ((i + 1) % 2 == 0)   chess_field_items[i]->set_color(200, 200, 200);
            else                    chess_field_items[i]->set_color(50, 50, 50);
        }

        row++;

        if (row == sqrt(size) + 1)
        {
            row = 1;
            column++;

            swap = !swap;
        }
    }
}