#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QString>

#include <functional>

struct Button : QPushButton
{
    Button(QWidget* parent);
    Button(QWidget* parent, std::function<void ()> slot);
    ~Button() = default;

    void                        set_color(int red, int green, int blue);
    void                        set_geometry(int x, int y, int w, int h);
    void                        set_text(QString text);
    void                        set_icon(QString path);

private:
    QWidget*                    parent;
    std::function<void ()>      slot;
    void                        click();
};

#endif // BUTTON_H