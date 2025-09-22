#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui/pixel.h"
#include "ui/button.h"

#include <QMainWindow>
#include <QWidget>
#include <QLabel>

#include <vector>


struct MainWindow : QMainWindow
{
    MainWindow(QWidget* parent);
    ~MainWindow() = default;


private:
    QWidget*                                central_widget;
    Button*                                 ok_button;
    Button*                                 probabilities_button;
    Button*                                 clear_button;
    QLabel*                                 neuro_result;
    QLabel*                                 neuro_result_pr;
    QLabel*                                 neuro_result_pr_tile;
    QString                                 probabilities_qstr          = "";
    std::vector<Pixel *>                    pixels;

    void                                    click_ok_button();
    void                                    click_clear_button();
    void                                    click_probabilities_button();
    std::vector<std::pair<int, int>>        run_neuro_model(std::vector<std::vector<int>> vector);
    std::vector<std::vector<int>>           convert_to_2d(const std::vector<int>& input);
    std::pair<int, int>                     find_max_probability(const std::vector<std::pair<int, int>>& predictions);
};

#endif // MAIN_WINDOW_H