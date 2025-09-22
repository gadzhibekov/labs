#include "text_edit.h"

TextEdit::TextEdit(QString text, QWidget* parent) : QLineEdit(parent)
{
    set_text(text);
}

TextEdit::~TextEdit()
{
    ;
}

void TextEdit::set_text(QString text)
{
    this->setText(text);
}

QString TextEdit::get_text()
{
    return this->text();
}

void TextEdit::set_text_size(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    this->setFont(font);
}