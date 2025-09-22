#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#define WHITE_HORSE_PATH "../res/white_horse.png"

#include "ui/map_item.h"
#include "ui/text_item.h"
#include "ui/button.h"

#include <QMainWindow>
#include <QWidget>

#include <vector>
#include <cstdlib>

struct MainWindow : QMainWindow
{
    MainWindow(QWidget* parent);
    ~MainWindow() = default;

private:
    QWidget*                central_widget;
    TextItem*               set_n_widget;
    TextItem*               set_m_widget;
    TextItem*               set_x_widget;
    TextItem*               set_y_widget;
    Button*                 regenerate_maze_button;
    std::vector<MapItem *>  maze;

    void generate_maze(uint8_t n, uint8_t m, uint8_t x, uint8_t y, bool&& is_show);
    void regenerate_maze_button_click();
    void draw_solution_on_maze(std::vector<std::vector<int>> board);
};

#endif // MAIN_WINDOW_H