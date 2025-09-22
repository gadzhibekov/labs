#pragma once

#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QLineEdit>
#include <QString>
#include <QWidget>

struct TextEdit : QLineEdit
{
    TextEdit(QString text, QWidget* parent);
    ~TextEdit();

    void    set_text_size(int size);
    void    set_text(QString text);
    QString get_text();
};

#endif // TEXT_EDIT_H