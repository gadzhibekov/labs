#ifndef MAP_ITEM_H
#define MAP_ITEM_H

#define MAP_ITEM_SIZE 50

#include "button.h"

#include <utility>

struct MapItem : Button
{
    MapItem(QWidget* parent, int id, std::pair<int, int> pair);
    ~MapItem() = default;

    std::pair<int, int>     get_coords()    const   { return pair; };
    int                     get_id()        const   { return id; }

private:    
    QWidget*                parent;
    std::pair<int, int>     pair;
    int                     id;

};

#endif // MAP_ITEM_H