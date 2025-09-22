#pragma once

#ifndef SECOND_WINDOW_H
#define SECOND_WINDOW_H

#include "ui/text.h"
#include "ui/text_edit.h"
#include "ui/button.h"

#include <QWidget>

struct SecondWindow : QWidget
{
    SecondWindow(int minimum_count_of_solutions, int maximum_count_of_solutions, int short_path);
    ~SecondWindow();

    void        click_ok_button();
    void        click_restart_button();
    void        click_show_map_button();

private:
    Text*       text_inf_1;
    Text*       text_inf_2;
    Text*       min_count_of_solutions;
    Text*       max_count_of_solutions;
    TextEdit*   index_of_solutions;
    Button*     ok;
    Button*     show_map;
    Button*     restart;
};

#endif // SECOND_WINDOW_H