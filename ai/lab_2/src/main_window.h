#pragma once

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#define FIELD_BUTTON_SIZE 50

#include "ui/item.h"
#include "ui/text.h"
#include "ui/button.h"
#include "ui/text_edit.h"
#include "second_window.h"
#include "params.h"

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>

#include <vector>

struct Item;

typedef std::vector<Item *>                                 IVector;
typedef std::vector<std::pair<int, int>>                    PVector;
typedef std::vector<std::vector<int>>                       IVVector;
typedef std::vector<std::vector<std::pair<int, int>>>       PVVector;

struct MainWindow : QMainWindow
{
    MainWindow(QWidget* parent, int size);
    ~MainWindow();

    static void         draw_path_on_map(PVector pair_vector);
    static void         draw_map(IVVector maze, int size);
    static void         show_initial_maze(IVVector maze, int size);
    static int          size_of_map;
    static IVector      map;
    static PVVector     solutions;
    static IVVector     map_2d;

    void                click_show_solutions_by_index_button();
    void                click_restart_button();
    void                click_show_maze_button();
    void                click_show_params_button();

private:
    SecondWindow*       second_window;
    ParamsWindow*       params;
    static QWidget*     central_widget;
    Text*               solutions_count_text;
    Text*               short_solutions_size_text;
    Text*               current_solutions_index_text;
    Button*             show_solutions_by_index_button;
    TextEdit*           index_of_solutions;
    Button*             restart_button;
    Button*             show_maze_button;
    Button*             show_params_button;


    void                generate_map(int size, IVVector& maze);
};

#endif // MAIN_WINDOW_H