#include "button.h"

#include <QPalette>
#include <QObject>

Button::Button(QWidget* parent) : QPushButton(parent)
{
    ;
}

Button::Button(QWidget* parent, std::function<void()> slot) : QPushButton(parent), slot(slot)
{
    QObject::connect(this, &Button::clicked, this, &Button::click);
}

void Button::set_geometry(int x, int y, int w, int h)
{
    setGeometry(x, y, w, h);
}

void Button::set_text(const QString& text)
{
    setText(text);
}

void Button::set_color(const Color& color)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, QColor(color.red, color.green, color.blue));
    this->setPalette(palette);
    this->update();
    this->color = color;
}

void Button::click()
{
    slot();
}