#include "pixel.h"

#include <iostream>

Pixel::Pixel(QWidget* parent, std::pair<uint, uint> corrds) : Button(parent), corrds(corrds)
{
    setMouseTracking(true);
}

void Pixel::enterEvent(QEvent* event)
{
    set_color(Color(0, 0, 0));

    QPushButton::enterEvent(event);
}

void Pixel::leaveEvent(QEvent* event) 
{
    QPushButton::leaveEvent(event);
}