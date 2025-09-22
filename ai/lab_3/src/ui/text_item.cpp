#include "text_item.h"

TextItem::TextItem(QWidget* parent, QString text_for_label, QString hold_text_for_line_edit) : parent(parent)
{
    co_parent = new QWidget(parent);
    line_edit = new QLineEdit(co_parent);
    label =     new QLabel(co_parent);


    label->setText(text_for_label);
    line_edit->setPlaceholderText(hold_text_for_line_edit);
}

void TextItem::set_geometry(int x, int y, int w, int h)
{
    co_parent->setGeometry(x, y, w, h);

    label->setGeometry(0, 0, w / 10, h);
    line_edit->setGeometry(w / 10, 0, w - (w / 10), h);
}

void TextItem::set_text_for_line_edit(QString text)
{
    line_edit->setText(text);
}