#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H

#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QWidget>

#include <utility>

struct TextItem
{
    TextItem(QWidget* parent, QString text_for_label, QString hold_text_for_line_edit);
    ~TextItem() = default;
    

    QString                 get_text_from_line_edit()   const   { return line_edit->text(); }
    QString                 get_text_from_label()       const   { return label->text(); }

    std::pair<int, int>     get_coords()                const   { return {co_parent->pos().x(), co_parent->pos().y()}; }
    std::pair<int, int>     get_size()                  const   { return {co_parent->width(),   co_parent->height()}; }


    void                    set_text_for_line_edit(QString text);
    void                    set_geometry(int x, int y, int w, int h);

private:
    QLineEdit*              line_edit;
    QLabel*                 label;
    QWidget*                parent;
    QWidget*                co_parent;
};

#endif // TEXT_ITEM_H