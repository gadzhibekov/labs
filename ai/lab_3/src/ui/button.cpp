#include "button.h"

#include <QPalette>
#include <QObject>
#include <QIcon>
#include <QSize>

Button::Button(QWidget* parent) : QPushButton(parent)
{
    ;
}

Button::Button(QWidget* parent, std::function<void()> slot) : QPushButton(parent), slot(slot)
{
    QObject::connect(this, &Button::clicked, this, &Button::click);
}

void Button::set_color(int red, int green, int blue)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, QColor(red, green, blue));
    this->setPalette(palette);
    this->update();
}

void Button::set_geometry(int x, int y, int w, int h)
{
    this->setGeometry(x, y, w, h);
}

void Button::set_text(QString text)
{
    this->setText(text);
}

void Button::click()
{
    slot();
}

void Button::set_icon(QString path)
{
    this->setIcon(QIcon(path));
    this->setIconSize(QSize(45, 45));
}