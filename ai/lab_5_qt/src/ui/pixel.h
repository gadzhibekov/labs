#ifndef PIXEL_H
#define PIXEL_H

#define PIXEL_SIZE 20

#include "button.h"

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>

#include <utility>
#include <cstdlib>


struct Pixel : Button
{
    Pixel(QWidget* parent, std::pair<uint, uint> corrds);
    ~Pixel() = default;

protected:
    void enterEvent(QEvent* event)              override;
    void leaveEvent(QEvent* event)              override;

private:
    std::pair<uint, uint>           corrds;
};

#endif // PIXEL_H