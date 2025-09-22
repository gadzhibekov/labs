#pragma once

#define FIELD_BUTTON_SIZE 80

#include <QPushButton>
#include <QWidget>
#include <QString>

#include <utility>

#include "player.h"

struct Player;

typedef std::pair<int, int>    Pair;

struct FieldButton : QPushButton
{
    FieldButton(QWidget* parent, int id, Pair coords);
    ~FieldButton() {};

    void            set_player(Player& player);
    void            set_text(const QString& text);
    void            set_color(int red, int green, int blue);
    void            delete_player();
    void            click_slot();

    QWidget*        get_parent()      { return parent; }
    Player          get_player()      { return player; }
    Pair            get_coords()      { return coords; }
    int             get_id()          { return id; }
    bool            is_active()       { return is_player_here; }

private:
    QWidget*        parent;
    Pair            coords;
    Player          player;
    int             id;
    bool            is_player_here = false;
};