#ifndef PARAMS_H
#define PARAMS_H

#include "ui/text.h"
#include "ui/button.h"

#include <QWidget>

struct ParamsWindow : QWidget
{
        ParamsWindow(QWidget* parent);
        ~ParamsWindow() = default;

        void            show_widget(int w, int h);
        void            hide_widget();

private:
        Text*           icon_1;
        Text*           icon_2;
        Text*           icon_3;
        Text*           icon_4;
        Text*           data_1;
        Text*           data_2;
        Text*           data_3;
        Text*           data_4;

        Button*         hide_window_button;
};

#endif // PARAMS_H