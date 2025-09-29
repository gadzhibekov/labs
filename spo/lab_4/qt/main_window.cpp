#include "main_window.h"

#include <QString>
#include <QLabel>
#include <QFont>

unsigned int ListWidgetItem::size = 0;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    central_widget  = new QWidget(this);

    this->setCentralWidget(central_widget);
    this->setMinimumSize(1600, 1000);
    this->setWindowTitle("lab04");

    buttons_widget = new QWidget(central_widget);
    buttons_widget->setStyleSheet("background-color: grey;");
    buttons_widget->setGeometry(5, 5, 792, 990);

    list_widget = new QWidget(central_widget);
    list_widget->setStyleSheet("background-color: grey;");
    list_widget->setGeometry(803, 5, 792, 990);

    save_to_db = new QPushButton(buttons_widget);
    save_to_db->setGeometry(246, 5, 300, 50);
    save_to_db->setText("Сохранить в БД");
    set_font_size(save_to_db, 15);

    information = new QPushButton(buttons_widget);
    information->setGeometry(246, 115, 300, 50);
    information->setText("О программе");
    set_font_size(information, 15);

    exit = new QPushButton(buttons_widget);
    exit->setGeometry(246, 170, 300, 50);
    exit->setText("Выход");
    set_font_size(exit, 15);

    check_box = new QCheckBox(buttons_widget);
    check_box->setGeometry(246, 60, 300, 50);
    check_box->setText("Скрытые");
    set_font_size(check_box, 15);

    add_item_to_list(list_widget, {"Название", "Цена", "Магазин"});
    add_item_to_list(list_widget, {"AMD Ryzen 7 3700X", "25 000", "DNS"});
    add_item_to_list(list_widget, {"NVidia RTX 2060 Super", "30 000", "Второй"});
    add_item_to_list(list_widget, {"Intel Core i7 9700KF", "30 000", "Второй"});
    add_item_to_list(list_widget, {"AMD RX 5700 XT", "30 000", "DNS"});
}

void add_item_to_list(QWidget* parent, ListWidgetItem list_data)
{
    QWidget* item = new QWidget(parent);
    item->setGeometry(0, ListWidgetItem::size * 50, 792, 50);

    QLabel* text_1 = new QLabel(item);
    text_1->setText(list_data.text_1);
    text_1->setGeometry(0, 0, 264, 50);
    set_font_size(text_1, 15);

    QLabel* text_2 = new QLabel(item);
    text_2->setText(list_data.text_2);
    text_2->setGeometry(264, 0, 264, 50);
    set_font_size(text_2, 15);

    QLabel* text_3 = new QLabel(item);
    text_3->setText(list_data.text_3);
    text_3->setGeometry(528, 0, 264, 50);
    set_font_size(text_3, 15);

    ListWidgetItem::size += 1;
}

void set_font_size(QWidget* widget, size_t font_size)
{
    QFont font = widget->font();
    font.setPointSize(static_cast<int>(font_size));
    widget->setFont(font);
}