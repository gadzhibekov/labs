#include "main_window.h"
#include "game.h"

#include <QString>
#include <QMessageBox>

#include <iostream>
#include <cmath>

MainWindow::MainWindow(QWidget* parent)
{
    central_widget = new QWidget(this);
    this->setCentralWidget(central_widget);
    this->setWindowTitle("Лаба3 (Виноградов Алексей)");

    uint8_t n = 6;
    uint8_t m = 6;
    uint8_t x = 1;
    uint8_t y = 1;

    generate_maze(n, m, x, y, false);
    
    this->setMinimumSize(MAP_ITEM_SIZE * static_cast<int>(n + 10), MAP_ITEM_SIZE * static_cast<int>(n + 2));
    this->setMaximumSize(MAP_ITEM_SIZE * static_cast<int>(n + 10), MAP_ITEM_SIZE * static_cast<int>(n + 2));

    set_n_widget = new TextItem(central_widget, "N", "Введите N");
    set_m_widget = new TextItem(central_widget, "M", "Введите M");
    set_x_widget = new TextItem(central_widget, "X", "Введите X");
    set_y_widget = new TextItem(central_widget, "Y", "Введите Y");

    set_n_widget->set_geometry(MAP_ITEM_SIZE * (n + 2), MAP_ITEM_SIZE, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE);
    set_m_widget->set_geometry((MAP_ITEM_SIZE * (n + 2)) + (MAP_ITEM_SIZE * 3) + 50, MAP_ITEM_SIZE, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE);
    set_x_widget->set_geometry(MAP_ITEM_SIZE * (n + 2), MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE);
    set_y_widget->set_geometry((MAP_ITEM_SIZE * (n + 2)) + (MAP_ITEM_SIZE * 3) + 50, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE);

    set_n_widget->set_text_for_line_edit(QString::number(static_cast<int>(n)));
    set_m_widget->set_text_for_line_edit(QString::number(static_cast<int>(m)));
    set_x_widget->set_text_for_line_edit(QString::number(static_cast<int>(x)));
    set_y_widget->set_text_for_line_edit(QString::number(static_cast<int>(y)));

    regenerate_maze_button = new Button(central_widget, [ & ] () {regenerate_maze_button_click();});
    regenerate_maze_button->set_geometry(MAP_ITEM_SIZE * (n + 2), MAP_ITEM_SIZE * 5, MAP_ITEM_SIZE * 6 + 50, MAP_ITEM_SIZE);
    regenerate_maze_button->set_text("Начать");
    regenerate_maze_button->set_color(0, 128, 0);


    std::vector<std::vector<int>> board(static_cast<int>(n), std::vector<int>(static_cast<int>(n), -1));

    board[static_cast<int>(x) - 1][static_cast<int>(y) - 1] = 0;


    if (game::solve_knights_tour(board, static_cast<int>(x) - 1, static_cast<int>(y) - 1, {2, 1, -1, -2, -2, -1, 1, 2}, {1, 2, 2, 1, -1, -2, -2, -1}, 1)) 
    {
        draw_solution_on_maze(board);
    } 
    else 
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Решения не найдены");
    }

    QMessageBox::information(nullptr, "Значения по-умолчанию", "N = 6\nM = 6\nX = 1\nY = 1\n\n\nЗначения по-умолчанию можно отредактировать в программе после запуска нажав на OK");
}

void MainWindow::generate_maze(uint8_t n, uint8_t m, uint8_t x, uint8_t y, bool&& is_show)
{
    bool swap = false;

    for (int i = 0, id = 1, row = 1, column = 1; i < static_cast<int>(n * m) ; ++i, id++)
    {
        maze.push_back(new MapItem(central_widget, id, {column, row}));
        maze[i]->setGeometry(row * MAP_ITEM_SIZE, column * MAP_ITEM_SIZE, MAP_ITEM_SIZE, MAP_ITEM_SIZE);
        
        if (column == static_cast<int>(x) && row == static_cast<int>(y))
            maze[i]->set_icon(WHITE_HORSE_PATH);

        if (is_show) 
            maze[i]->show();

        if (swap)
        {
            if (i % 2 == 0)             maze[i]->set_color(200, 200, 200);
            else                        maze[i]->set_color(50, 50, 50);
        }
        else
        {
            if ((i + 1) % 2 == 0)       maze[i]->set_color(200, 200, 200);
            else                        maze[i]->set_color(50, 50, 50);
        }

        row++;

        if (row == sqrt(static_cast<int>(n * m)) + 1)
        {
            row = 1;
            column++;

            swap = !swap;
        }
    }
}

void MainWindow::regenerate_maze_button_click()
{
    QString n_str = set_n_widget->get_text_from_line_edit();
    QString m_str = set_m_widget->get_text_from_line_edit();
    QString x_str = set_x_widget->get_text_from_line_edit();
    QString y_str = set_y_widget->get_text_from_line_edit();

    bool ok1, ok2, ok3, ok4;

    int n_int = n_str.toInt(&ok1);
    int m_int = m_str.toInt(&ok2);
    int x_int = x_str.toInt(&ok3);
    int y_int = y_str.toInt(&ok4);

    if ((ok1 && ok2 && ok3 && ok4) && (n_int == m_int) && (n_int > 0 && m_int > 0) && (x_int < n_int && y_int < m_int))
    {
        this->setMinimumSize(MAP_ITEM_SIZE * (n_int + 10), MAP_ITEM_SIZE * (m_int + 2));
        this->setMaximumSize(MAP_ITEM_SIZE * (n_int + 10), MAP_ITEM_SIZE * (m_int + 2));

        set_n_widget->set_geometry(MAP_ITEM_SIZE * (n_int + 2), MAP_ITEM_SIZE, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE);
        set_m_widget->set_geometry((MAP_ITEM_SIZE * (n_int + 2)) + (MAP_ITEM_SIZE * 3) + 50, MAP_ITEM_SIZE, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE);
        set_x_widget->set_geometry(MAP_ITEM_SIZE * (n_int + 2), MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE);
        set_y_widget->set_geometry((MAP_ITEM_SIZE * (n_int + 2)) + (MAP_ITEM_SIZE * 3) + 50, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE * 3, MAP_ITEM_SIZE);
        regenerate_maze_button->set_geometry(MAP_ITEM_SIZE * (n_int + 2), MAP_ITEM_SIZE * 5, MAP_ITEM_SIZE * 6 + 50, MAP_ITEM_SIZE);


        for (auto ptr : maze)
        {
            if (ptr != nullptr) 
            {
                delete ptr;
                ptr = nullptr;
            }
        }
        maze.clear();

        generate_maze(static_cast<uint8_t>(n_int), static_cast<uint8_t>(m_int), static_cast<uint8_t>(x_int), static_cast<uint8_t>(y_int), true);

        std::vector<std::vector<int>> board(static_cast<int>(n_int), std::vector<int>(static_cast<int>(n_int), -1));

        board[static_cast<int>(x_int) - 1][static_cast<int>(y_int) - 1] = 0;


        if (game::solve_knights_tour(board, static_cast<int>(x_int) - 1, static_cast<int>(y_int) - 1, {2, 1, -1, -2, -2, -1, 1, 2}, {1, 2, 2, 1, -1, -2, -2, -1}, 1)) 
        {
            draw_solution_on_maze(board);
        } 
        else 
        {
            QMessageBox::warning(nullptr, "Предупреждение", "Решения не найдены");
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "Ошибка", "Введены неккоректные данные");
    }
}

void MainWindow::draw_solution_on_maze(std::vector<std::vector<int>> board)
{
    std::vector<int> maze_2d;

    for (const auto& innerVec : board) 
    {
        for (int num : innerVec)
        {
            maze_2d.push_back(num);
        }
    }

    for (int i = 0; i < maze_2d.size(); ++i)
    {
        if (maze_2d[i] == 0)
            continue;

        maze[i]->set_text(QString::number(maze_2d[i]));
    }

}