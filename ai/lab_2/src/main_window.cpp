#include "main_window.h"
#include "game.h"
#include "ui/color.h"
#include "log/log.h"

#include <QProcess>
#include <QCoreApplication>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

IVector         MainWindow::map;
PVVector        MainWindow::solutions;
IVVector        MainWindow::map_2d;
QWidget*        MainWindow::central_widget;
int             MainWindow::size_of_map;

MainWindow::MainWindow(QWidget* parent, int size) : QMainWindow(parent)
{
    srand(time(0));
    
    central_widget = new QWidget(this);
    this->setCentralWidget(central_widget);
    this->setMinimumSize(FIELD_BUTTON_SIZE * (size + 2) + 400, FIELD_BUTTON_SIZE * (size + 2));
    this->setMaximumSize(FIELD_BUTTON_SIZE * (size + 2) + 400, FIELD_BUTTON_SIZE * (size + 2));
    this->setWindowTitle("Лаба 2 (Алексей Виноградов)");

    Text*               solutions_count_text;
    Text*               short_solutions_text;
    Button*             restart_button;
    Button*             show_maze_button;

    MainWindow::size_of_map = size;

    IVVector maze(size, vector<int>(size));

    generate_map(size, maze);
    MainWindow::map_2d = maze;
    solutions = Game::find_all_paths(maze, size);


    std::vector<int> pathes_size;
    for (auto path : solutions)
    {
        pathes_size.push_back(path.size());
    }

    auto min_it = std::min_element(pathes_size.begin(), pathes_size.end());
    PVector short_path;
    int short_path_index;

    for (int i = 0; i < solutions.size(); ++i)
    {
        if (solutions[i].size() == *min_it)
        {
            short_path = solutions[i];
            short_path_index = i;
            break;
        }
    }

    draw_path_on_map(short_path);

#ifdef WITH_LOG
    std::cout << "Общее количество решений: " << solutions.size() << std::endl;

    if (solutions.size() != 0)
    {
        std::cout << "Самое короткое решение: "   << *min_it << std::endl;
    }
#endif // WITH_LOG


    if (solutions.size() != 0)
    {
        second_window = new SecondWindow(1, solutions.size(), *min_it);
    }
    else
    {
        second_window = new SecondWindow(0, 0, 0);
    }


    solutions_count_text            = new Text("Всего маршрутов найдено: " + QString::number(solutions.size()),      this);
    short_solutions_size_text       = new Text("Размер самого короткого маршрута: " + QString::number(*min_it),      this);
    current_solutions_index_text    = new Text("Индекс текущего маршрута: " + QString::number(short_path_index + 1), this);
    restart_button                  = new Button([&](){click_restart_button();}, this, "");
    show_maze_button                = new Button([&](){click_show_maze_button();}, this, "");
    show_params_button              = new Button([&](){click_show_params_button();}, this, "");
    show_solutions_by_index_button  = new Button([&](){click_show_solutions_by_index_button();}, this, "Просмотреть маршрут с индексом");
    index_of_solutions              = new TextEdit("0", this);

    solutions_count_text->setGeometry((MainWindow::map_2d.size() + 2) * FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE, 400, 50);
    short_solutions_size_text->setGeometry((MainWindow::map_2d.size() + 2) * FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE * 2, 400, 50);
    current_solutions_index_text->setGeometry((MainWindow::map_2d.size() + 2) * FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE * 3, 400, 50);
    show_solutions_by_index_button->setGeometry((MainWindow::map_2d.size() + 2) * FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE * 4, 300, 50);
    index_of_solutions->setGeometry((MainWindow::map_2d.size() + 2) * FIELD_BUTTON_SIZE + 300, FIELD_BUTTON_SIZE * 4, 50, 50);
    restart_button->setGeometry((MainWindow::map_2d.size() + 2) * FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE * 5, 50, 50);
    show_maze_button->setGeometry((MainWindow::map_2d.size() + 2) * FIELD_BUTTON_SIZE + 60, FIELD_BUTTON_SIZE * 5, 50, 50);
    show_params_button->setGeometry((MainWindow::map_2d.size() + 2) * FIELD_BUTTON_SIZE + 120, FIELD_BUTTON_SIZE * 5, 50, 50);

    solutions_count_text->set_text_size(15);
    short_solutions_size_text->set_text_size(15);
    current_solutions_index_text->set_text_size(15);
    show_solutions_by_index_button->set_text_size(12);
    index_of_solutions->set_text_size(15);

    restart_button->set_icon("../res/restart.png", 40);
    show_maze_button->set_icon("../res/show.png", 40);
    show_params_button->set_icon("../res/inf.png", 40);

    index_of_solutions->setAlignment(Qt::AlignCenter);

    // second_window->show();

    params         = new ParamsWindow(this);
}

MainWindow::~MainWindow()
{
    delete second_window;
}

void MainWindow::draw_path_on_map(PVector pair_vector)
{
    std::vector<int> result;

    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < pair_vector.size(); ++j)
        {
            if ((pair_vector[j].first + 1 == map[i]->get_coords().second && pair_vector[j].second + 1 == map[i]->get_coords().first))
            {
                result.push_back(map[i]->get_index());
            }

            map[i]->delete_icon();
        }
    }

    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < map.size(); ++j)
        {
            if (map[j]->get_index() == result[i])
            {
                if (map[j]->get_value() == 7) map[j]->set_icon("../res/start.png", 40);
                if (map[j]->get_value() == 9) map[j]->set_icon("../res/end.png", 40);
                if (map[j]->get_value() == 1) map[j]->set_icon("../res/h.png", 25);
                if (map[j]->get_value() == 0) map[j]->set_icon("../res/wall.png", 40);
            }
        }
    }
}

void MainWindow::generate_map(int size, IVVector& maze)
{
    Game::generate_map(maze, size);
    MainWindow::draw_map(maze, size);

#ifdef WITH_LOG
    Game::print_map(maze);
#endif // WITH_LOG
}

void MainWindow::draw_map(IVVector maze, int size)
{
    map.clear();
    std::vector<int> flat_vector;

    for (const auto& inner_vec : maze) 
    {
        flat_vector.insert(flat_vector.end(), inner_vec.begin(), inner_vec.end());
    }

    for (int i = 0, row = 1, column = 1; i < flat_vector.size(); ++i)
    {   
        map.push_back(new Item(central_widget, {row, column}, flat_vector[i], i + 1));
        map[i]->setGeometry(row * FIELD_BUTTON_SIZE, column * FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE);

        row++;

        if (row == size + 1)
        {
            row = 1;
            column++;
        }
    }
}

void MainWindow::show_initial_maze(IVVector maze, int size)
{
    std::vector<int> flat_vector;

    for (const auto& inner_vec : maze) 
    {
        flat_vector.insert(flat_vector.end(), inner_vec.begin(), inner_vec.end());
    }

    for (int i = 0; i < flat_vector.size(); ++i)
    {
        if (flat_vector[i] == 7) map[i]->set_icon("../res/start.png", 40);
        if (flat_vector[i] == 9) map[i]->set_icon("../res/end.png", 40);
        if (flat_vector[i] == 1) map[i]->set_icon("../res/h.png", 25);
        if (flat_vector[i] == 0) map[i]->set_icon("../res/wall.png", 40);
    }
}

void MainWindow::click_show_solutions_by_index_button()
{    
    bool ok;
    
    int number = index_of_solutions->get_text().toInt(&ok);

    if (ok) 
    {
        if (0 < number && number <= MainWindow::solutions.size())
        {
            MainWindow::draw_path_on_map(MainWindow::solutions[number - 1]);
        }
        else
        {
            LogWithError("Введите число в допустимом диапазоне");    
        }
    } 
    else 
    {
        LogWithError("Недопустимые символы");
    }
}

void MainWindow::click_restart_button()
{
    QProcess::startDetached(QCoreApplication::applicationFilePath(), QStringList());
    QCoreApplication::quit();
}

void MainWindow::click_show_maze_button()
{
    MainWindow::show_initial_maze(MainWindow::map_2d, MainWindow::size_of_map);
}

void MainWindow::click_show_params_button()
{
    params->show_widget(this->width(), this->height());
}