#pragma once

#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include "ui/text.h"
#include "ui/text_edit.h"
#include "ui/button.h"

#include <QDialog>

struct DialogWindow : QDialog
{
    DialogWindow();
    ~DialogWindow();

    void        click_ok_button();
    int         get_maze_size();
    
private:
    int         maze_size;
    TextEdit*   maze_size_text_edit;
    Button*     ok;
};

#endif // DIALOG_WINDOW_H