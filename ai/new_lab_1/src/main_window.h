#pragma once

#define FIELD_SIZE 8*8

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <vector>

#include "ui/field_button.h"

struct FieldButton;

typedef std::vector<FieldButton *> FBVector;

struct MainWindow : QMainWindow
{
    MainWindow(QWidget* parent);
    ~MainWindow() {}

    static FBVector         chess_field_items;
    static std::vector<int> positions;
    static QLabel*          results;

private:
    QWidget*                central_widget;
    QLabel*                 bk_icon;
    QLabel*                 wk_icon;
    QLabel*                 wr_icon;
    QLabel*                 bk_text;
    QLabel*                 wk_text;
    QLabel*                 wr_text;
    void                    generate_field(int size);
};  