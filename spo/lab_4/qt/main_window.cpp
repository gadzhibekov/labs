#include "main_window.h"
#include "../db.h"

#include <QString>
#include <QLabel>
#include <QFont>
#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QLayout>
#include <QLayoutItem>

#include <iostream>
#include <vector>

unsigned int ListWidgetItem::size   = 0;
bool                        is_hide = false;

struct table_element;

std::vector<QWidget *> list_elements;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    central_widget  = new QWidget(this);

    this->setCentralWidget(central_widget);
    this->setMinimumSize(1600, 1000);
    this->setMaximumSize(1600, 1000);

    #ifdef __linux__
    this->setWindowTitle("lab04 by Lnux");
    #elif defined(__WIN32)
    this->setWindowTitle("lab04 by Windows");
    #endif // __linux__

    buttons_widget = new QWidget(central_widget);
    buttons_widget->setStyleSheet("background-color: grey;");
    buttons_widget->setGeometry(5, 5, 400, 990);

    list_widget = new QWidget(central_widget);
    list_widget->setStyleSheet("background-color: grey;");
    list_widget->setGeometry(410, 5, 1185, 990);

    information = new QPushButton(buttons_widget);
    information->setGeometry(50, 60, 300, 50);
    information->setText("О программе");
    set_font_size(information, 15);

    exit = new QPushButton(buttons_widget);
    exit->setGeometry(50, 115, 300, 50);
    exit->setText("Выход");
    set_font_size(exit, 15);

    check_box = new QCheckBox(buttons_widget);
    check_box->setGeometry(50, 5, 300, 50);
    check_box->setText("Скрытые");
    set_font_size(check_box, 15);

    QObject::connect(information, &QPushButton::clicked, this, &MainWindow::information_slot);
    QObject::connect(exit, &QPushButton::clicked, this, &MainWindow::exit_slot);
    QObject::connect(check_box, &QCheckBox::stateChanged, this, &MainWindow::check_box_slot);

    add_item_to_list(list_widget, {"Номер", "Название", "Цена", "Наличие"});

    std::vector<table_element> table = get_products_table();

    for (auto i : table)
    {
        add_item_to_list(list_widget, {QString::fromStdString(i.id)
                                    , QString::fromStdString(i.name) 
                                    , QString::fromStdString(i.price)
                                    , QString::fromStdString(i.availability)});
    }
}

void MainWindow::exit_slot()
{
    QApplication::quit();
}

void MainWindow::information_slot()
{   
    QMessageBox::information(nullptr, "О программе", "Лабораторная работа 4\n---> Разработка кроссплатформенных программ\n---> Выполнил: Гаджибеков Б.Г\n---> Группа: 601-21");
}

void MainWindow::check_box_slot(int state)
{
    clear_list(list_widget);
    add_item_to_list(list_widget, {"Номер", "Название", "Цена", "Наличие"});

    std::vector<table_element> table;

    if (state == Qt::Checked)   table = get_visible_products_table();
    else                        table = get_products_table();

    for (auto i : table)
    {
        add_item_to_list(list_widget, {QString::fromStdString(i.id)
                                    ,  QString::fromStdString(i.name) 
                                    ,  QString::fromStdString(i.price)
                                    ,  QString::fromStdString(i.availability)});
    }
}

void add_item_to_list(QWidget* parent, ListWidgetItem list_data)
{
    QWidget* item = new QWidget(parent);
    item->setGeometry(0, ListWidgetItem::size * 50, 1185, 50);
    
    parent->show();
    
    QLabel* text_1 = new QLabel(item);
    text_1->setText(list_data.text_1);
    text_1->setGeometry(0, 0, 100, 50);
    text_1->setAlignment(Qt::AlignCenter);
    set_font_size(text_1, 15);
    text_1->show();

    QLabel* text_2 = new QLabel(item);
    text_2->setText(list_data.text_2);
    text_2->setGeometry(100, 0, 501, 50);
    set_font_size(text_2, 15);
    text_2->show();

    QLabel* text_3 = new QLabel(item);
    text_3->setText(list_data.text_3);
    text_3->setGeometry(601, 0, 292, 50);
    set_font_size(text_3, 15);
    text_3->show();

    QLabel* text_4 = new QLabel(item);
    text_4->setText(list_data.text_4);
    text_4->setGeometry(893, 0, 292, 50);
    set_font_size(text_4, 15);
    text_4->show();

    ListWidgetItem::size += 1;
    list_elements.push_back(item);
    
    item->show();
    item->update();
}

void clear_list(QWidget* parent)
{
    for (QWidget* item : list_elements) 
    {
        item->deleteLater();
    }

    list_elements.clear();
    
    ListWidgetItem::size = 0;
    
    parent->update();
}

void set_font_size(QWidget* widget, size_t font_size)
{
    QFont font = widget->font();
    font.setPointSize(static_cast<int>(font_size));
    widget->setFont(font);
}