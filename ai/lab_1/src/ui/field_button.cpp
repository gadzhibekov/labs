#include "field_button.h"
#include "icon.h"
#include "game.h"
#include "log/log.h"
#include "main_window.h"

#include <QString>
#include <QObject>
#include <QSize>
#include <QPalette>

#include <string>
#include <iostream>
#include <vector>

FieldButton::FieldButton(QWidget* parent, int id, Pair coords) : QPushButton(parent), parent(parent), id(id), coords(coords)
{
    QObject::connect(this, &FieldButton::clicked, this, &FieldButton::click_slot);  
    this->setStyleSheet("font-size: 20px;");
    this->setIconSize(QSize(64, 64));
}

void FieldButton::set_color(int red, int green, int blue)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, QColor(red, green, blue));
    this->setPalette(palette);
    this->update();
}

void FieldButton::set_player(Player& player)
{
    if (!is_player_here)
    {
        if (player.get_type() == PlayerType::BLACK_KING)
        {
            delete_bk_from_field();

            MainWindow::positions[0] = get_id();

            std::vector<int> solutions = check_check_and_stalemate(MainWindow::positions[0], MainWindow::positions[1], MainWindow::positions[2], MainWindow::positions[3]);

            clear();

            QString res = "( ";

            for (int p : solutions) 
            {
                int x, y;

                std::string pm;

                if (p > 100)
                {
                    pm = " (Пат)";

                    p -= 100;

                    y = p % 10;
                    x = ((p - y) / 10) % 100;

                    draw_on_map({x, y}, MainWindow::chess_field_items, (QString)"П");
                }
                else
                {
                    pm = " (Мат)";

                    y = p % 10;
                    x = ((p - y) / 10) % 100;

                    draw_on_map({x, y}, MainWindow::chess_field_items, (QString)"M");
                }


                std::cout << "[x, y] = " << "[" << x << ", " << y << "]" << pm << std::endl;
                // res += (QString::number(p) + "  ");
            }

            std::cout << "\n\n\n";

            // res += ")";

            // std::cout << "Паты и маты: " << res.toStdString() << std::endl;

            // MainWindow::results->setText((QString)"Паты и маты: " + res);
        }

        this->player = player;
        player.set_location(id);
        this->setIcon(Icon(player.get_icon()));
        is_player_here = true;
    }
    else
    {
        LogWithError("Поле уже занято другой фигурой");
    }
}

void FieldButton::delete_player()
{
    this->setIcon(Icon());
    is_player_here = false;
}

void FieldButton::click_slot()
{   
    Player player_bk = Player(PlayerType::BLACK_KING, Icon(BLACK_KING_PATH));

    set_player(player_bk);
}

void FieldButton::set_text(const QString& text)
{
    this->setText(text);
}