#include "main_window.h"
#include "nn/neural.h"

#include <cmath>
#include <iostream>
#include <utility>
#include <algorithm>

#include <QFont>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) 
{
    central_widget = new QWidget(this);
    this->setCentralWidget(central_widget);
    this->setMinimumSize(1000, 600);
    this->setMaximumSize(1000, 600);
    this->setWindowTitle("Лаба 5 (Алексей Виноградов)");

    for (int i = 0, row = 1, column = 1; i < 28 * 28 ; ++i)
    {
        pixels.push_back(new Pixel(central_widget, {row, column}));
        pixels[i]->set_geometry(row * PIXEL_SIZE, column * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE);
        pixels[i]->set_color(Color(255, 255, 255));
        
        row++;

        if (row == sqrt(28 * 28) + 1)
        {
            row = 1;
            column++;
        }
    }

    neuro_result = new QLabel(central_widget);
    ok_button = new Button(central_widget, [ & ] () {click_ok_button();});
    clear_button = new Button(central_widget, [ & ] () {click_clear_button();});
    probabilities_button = new Button(central_widget, [ & ] () {click_probabilities_button();});
    neuro_result_pr_tile = new QLabel(central_widget);
    neuro_result_pr = new QLabel(central_widget);

    neuro_result->setGeometry(590, 20, 400, 440);
    neuro_result_pr_tile->setGeometry(835, 110, 400, 50);
    neuro_result_pr->setGeometry(835, 150, 400, 50);
    ok_button->set_geometry(590, 530, 130, 50);
    clear_button->set_geometry(795 - 70, 530, 130, 50);
    probabilities_button->set_geometry(795 - 70 + 130 + 10, 530, 130, 50);

    ok_button->set_text("Распознать");
    clear_button->set_text("Очистить");
    probabilities_button->set_text("Вероятности");
    neuro_result->setText("Нажмите на кнопку cтарт");
    neuro_result->setFont(QFont("Arial", 25));
    neuro_result->setAlignment(Qt::AlignCenter);
    neuro_result_pr_tile->setFont(QFont("Arial", 16));
    neuro_result_pr->setFont(QFont("Arial", 38));
}

void MainWindow::click_ok_button()
{
    neuro_result->setGeometry(590 - 50, 20, 400, 440);

    std::vector<int> pixels_ints(28*28);

    for (int i = 0; i < pixels.size() ; ++i)
    {
        if (pixels[i]->get_color() == Color(255, 255, 255))
        {
            pixels_ints[i] = 0;
        }
        if (pixels[i]->get_color() == Color(0, 0, 0))
        {
            pixels_ints[i] = 1;
        }
    }

    std::vector<std::vector<int>> pixels_ints_2d = convert_to_2d(pixels_ints);

    #ifdef WITH_LOG
    for (const auto& row : pixels_ints_2d) 
    {
        for (const auto& elem : row)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Предсказанная цифра: " << run_neuro_model(pixels_ints_2d) << std::endl;
    #endif //WITH_LOG

    neuro_result->setFont(QFont("Arial", 250));

    std::vector<std::pair<int, int>>  nn_result         = run_neuro_model(pixels_ints_2d);
    std::pair<int, int>               best_nn_result    =   find_max_probability(nn_result);


    for (int i = 0; i < nn_result.size(); ++i)
    {
        probabilities_qstr += "Цифра " + QString::number(nn_result[i].first) + " с вероятностью " + QString::number(nn_result[i].second) + "\n";
    }

    neuro_result->setText(QString::number(best_nn_result.first));
    neuro_result_pr_tile->setText("с вероятностью");
    neuro_result_pr->setText(QString::number(best_nn_result.second));
}

void MainWindow::click_clear_button()
{
    for (int i = 0; i < pixels.size() ; ++i)
    {
        pixels[i]->set_color(Color(255, 255, 255));
    }
    
    neuro_result->setGeometry(590, 20, 400, 440);
    neuro_result->setFont(QFont("Arial", 25));
    neuro_result->setText("Нажмите на кнопку распознать");
    neuro_result_pr_tile->setText("");
    neuro_result_pr->setText("");
}

std::vector<std::vector<int>> MainWindow::convert_to_2d(const std::vector<int>& input)
{
    const int rows = 28;
    const int cols = 28;
    
    if (input.size() != rows * cols) 
    {
        throw std::invalid_argument("Input vector must have exactly 784 elements.");
    }

    std::vector<std::vector<int>> output(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            output[i][j] = input[i * cols + j];
        }
    }

    return output;
}

std::vector<std::pair<int, int>> MainWindow::run_neuro_model(std::vector<std::vector<int>> vector)
{
    Mat digit_image = Neural::vector_to_mat(vector);
    
    Ptr<ANN_MLP> neuralNet = ANN_MLP::load("../src/nn/model/trained_model/neuro_model.xml");
    
    if (neuralNet.empty()) 
    {
        std::cerr << "Ошибка: не удалось загрузить модель improved_mnist_model.xml!" << std::endl;
        return {};
    }

    Mat inputFlattened = Neural::preprocess_image(digit_image);
    
    Mat result;
    neuralNet->predict(inputFlattened, result);

    std::vector<std::pair<int, int>> predictions;
    for (int i = 0; i < result.cols; ++i) 
    {
        float probability = result.at<float>(0, i);
        predictions.emplace_back(i, static_cast<int>(probability * 100));
    }
    
    return predictions;
}

std::pair<int, int> MainWindow::find_max_probability(const std::vector<std::pair<int, int>>& predictions) 
{
    if (predictions.empty()) 
    {
        throw std::runtime_error("Вектор пуст!");
    }

    auto maxElement = std::max_element(predictions.begin(), predictions.end(),
    [](const std::pair<int, int>& a, const std::pair<int, int>& b)
    {
        return a.second < b.second;
    });

    return *maxElement;
}

void MainWindow::click_probabilities_button()
{
    QMessageBox::information(nullptr, "Вероятности", probabilities_qstr != "" ? probabilities_qstr : "Нет данных");
}