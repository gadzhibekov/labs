#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QCheckBox>

struct MainWindow : QMainWindow
{
    MainWindow(QWidget* parent);

private:
    QWidget*        central_widget;
    QWidget*        buttons_widget;
    QWidget*        list_widget;
    QPushButton*    save_to_db;
    QPushButton*    information;
    QPushButton*    exit;
    QCheckBox*      check_box;
};

struct ListWidgetItem
{
    QString text_1, text_2, text_3;
    static unsigned int size;
};

void add_item_to_list(QWidget* parent, ListWidgetItem list_data);
void set_font_size(QWidget* widget, size_t font_size);

#endif // MAIN_WINDOW_H