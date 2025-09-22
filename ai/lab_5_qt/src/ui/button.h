#ifndef BUTTON_H
#define BUTTON_H

#include "color.h"

#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QEvent>
#include <QMouseEvent>

#include <functional>

struct Button : QPushButton
{
    Button(QWidget* parent);
    Button(QWidget* parent, std::function<void()> slot);
    ~Button() = default;

    void set_geometry(int x, int y, int w, int h);
    void set_color(const Color& color);
    void set_text(const QString& text);

    Color get_color() const { return this->color; }


protected:
    virtual void enterEvent(QEvent* event)              override {};
    virtual void leaveEvent(QEvent* event)              override {};

private:
    std::function<void ()>      slot;
    Color                       color;
    void                        click();
};

#endif //BUTTON_H