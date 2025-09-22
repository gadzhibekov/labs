#include "button.h"

#include <QObject>
#include <QIcon>

Button::Button(std::function<void()> slot, QWidget* parent, QString text) : QPushButton(parent), parent(parent), slot(slot)
{
    set_text(text);
    QObject::connect(this, &Button::clicked, this, &Button::click_slot);
}

Button::~Button()
{
    ;
}

void Button::click_slot()
{
    slot();
}

void Button::set_text(QString text)
{
    this->setText(text);
}

void Button::set_text_size(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    this->setFont(font);
}

void Button::set_icon(const QString& path, int size)
{
    QIcon icon(path);
    this->setIcon(icon);
    this->setIconSize(QSize(size, size));

    this->setStyleSheet("QPushButton { background: transparent; border: none; }");
}