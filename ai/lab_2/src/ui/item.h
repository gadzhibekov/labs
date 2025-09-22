#pragma once

#ifndef ITEM_H
#define ITEM_H

#include "color.h"

#include <QPushButton>
#include <QWidget>
#include <QString>

#include <utility>
#include <vector>

struct Color;

typedef std::pair<int, int> Coords;

struct Item : QPushButton
{
    Item(QWidget* parent, Coords coords, int value, int index);
    ~Item();

    Coords              get_coords() { return coords; }
    int                 get_value()  { return value;  }
    int                 get_index()  { return index;  }

    void                set_coords(Coords coords);
    void                set_value(int value);
    void                set_index(int index);

    void                show_value();
    void                set_color(Color color);
    void                click_slot();
    void                clear();

    void                set_icon(const QString& path, int size);
    void                delete_icon();

private:
    QWidget*            parent;
    Coords              coords;
    int                 value;
    int                 index;
};

#endif // ITEM_H