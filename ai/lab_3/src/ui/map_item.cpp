#include "map_item.h"

#include <QFont>
#include <QPalette>
#include <QColor>

MapItem::MapItem(QWidget* parent, int id, std::pair<int, int> pair) 
: Button(parent), id(id), pair(pair)
{
    QFont font = this->font();
    font.setPointSize(30);
    this->setFont(font);

    QPalette pal = this->palette();
    pal.setColor(QPalette::ButtonText, QColor(128, 128, 128));
    this->setPalette(pal);
}