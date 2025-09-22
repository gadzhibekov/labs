#include "ui.h"
#include "algo.h"

#include <QIcon>
#include <QPalette>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    CentralWidget = new QWidget(this);

    this->setCentralWidget(CentralWidget);
    this->setMinimumSize(500, 580);
    this->setMaximumSize(500, 580);
    this->setWindowTitle("Лабораторная работа 6");

    Title = new QLabel(CentralWidget);
    Title->setText("Пожалуйста, определите параметры \nпопуляции и число элементов");
    Title->setGeometry(50, 30, 400, 50);
    SetSizeForLabel(15, Title);


    LabelParam1 = new QLabel(CentralWidget);
    LabelParam1->setText("Задайте число элементов:");
    LabelParam1->setGeometry(100, 100, 250, 50);
    SetSizeForLabel(14, LabelParam1);

    LineEditParam1 = new QLineEdit(CentralWidget);
    LineEditParam1->setGeometry(370, 100, 50, 50);


    LabelParam2 = new QLabel(CentralWidget);
    LabelParam2->setText("Введите размер популяции:");
    LabelParam2->setGeometry(100, 160, 250, 50);
    SetSizeForLabel(14, LabelParam2);

    LineEditParam2 = new QLineEdit(CentralWidget);
    LineEditParam2->setGeometry(370, 160, 50, 50);


    LabelParam3 = new QLabel(CentralWidget);
    LabelParam3->setText("Введите число поколений:");
    LabelParam3->setGeometry(100, 220, 250, 50);
    SetSizeForLabel(14, LabelParam3);

    LineEditParam3 = new QLineEdit(CentralWidget);
    LineEditParam3->setGeometry(370, 220, 50, 50);


    LabelParam4 = new QLabel(CentralWidget);
    LabelParam4->setText("Введите вероятность кроссовера (%):");
    LabelParam4->setGeometry(30, 280, 335, 50);
    SetSizeForLabel(14, LabelParam4);

    LineEditParam4 = new QLineEdit(CentralWidget);
    LineEditParam4->setGeometry(370, 280, 50, 50);


    LabelParam5 = new QLabel(CentralWidget);
    LabelParam5->setText("Введите вероятность мутаций (%):");
    LabelParam5->setGeometry(30, 340, 335, 50);
    SetSizeForLabel(14, LabelParam5);

    LineEditParam5 = new QLineEdit(CentralWidget);
    LineEditParam5->setGeometry(370, 340, 50, 50);

    
    LabelParam6 = new QLabel(CentralWidget);
    LabelParam6->setText("Ограничение по итоговой сумме:");
    LabelParam6->setGeometry(30, 400, 335, 50);
    SetSizeForLabel(14, LabelParam6);

    LineEditParam6 = new QLineEdit(CentralWidget);
    LineEditParam6->setGeometry(370, 400, 50, 50);

    Start = new QPushButton(CentralWidget);
    Start->setGeometry(10, 500, 50, 50);
    Start->setIcon(QIcon("../res/run.png"));
    Start->setIconSize(Start->size());
    Start->setStyleSheet("background-color: transparent; border: none;");
    QObject::connect(Start, &QPushButton::clicked, this, &MainWindow::StartSlot);

    Params = new QPushButton(CentralWidget);
    Params->setText("Параметры");
    Params->setGeometry(70, 500, 133, 50);
    SetSizeForButton(12, Params);
    SetColorForButton(QColor(33, 156, 49), Params);
    QObject::connect(Params, &QPushButton::clicked, this, &MainWindow::ParamsDataShowSlot);

    Solutions = new QPushButton(CentralWidget);
    Solutions->setText("Решения");
    Solutions->setGeometry(213, 500, 133, 50);
    SetSizeForButton(12, Solutions);
    SetColorForButton(QColor(33, 156, 49), Solutions);
    QObject::connect(Solutions, &QPushButton::clicked, this, &MainWindow::SolutionsDataShowSlot);

    Table = new QPushButton(CentralWidget);
    Table->setText("Таблица");
    Table->setGeometry(356, 500, 133, 50);
    SetSizeForButton(12, Table);
    SetColorForButton(QColor(33, 156, 49), Table);
    QObject::connect(Table, &QPushButton::clicked, this, &MainWindow::TableDataShowSlot);
}

void MainWindow::SetColorForButton(QColor color, QPushButton* Button)
{
    QPalette palette = Button->palette();
    palette.setColor(QPalette::Button, color);
    Button->setPalette(palette);
}

void MainWindow::SetSizeForLabel(int Size, QLabel* Label)
{
    Label->setAlignment(Qt::AlignCenter);
    QFont font = Label->font();
    font.setPointSize(Size);
    Label->setFont(font);
}

void MainWindow::SetSizeForButton(int Size, QPushButton* Button)
{
    QFont font = Button->font();
    font.setPointSize(Size);
    Button->setFont(font);
}

void MainWindow::StartSlot()
{
    mt19937 rng((unsigned) time(0));

    int  param1 = std::stoi(LineEditParam1->text().toStdString());
    int  param2 = std::stoi(LineEditParam2->text().toStdString());
    int  param3 = std::stoi(LineEditParam3->text().toStdString());
    int  param4 = std::stoi(LineEditParam4->text().toStdString());
    int  param5 = std::stoi(LineEditParam5->text().toStdString());
    int  param6 = std::stoi(LineEditParam6->text().toStdString());

    if (param1 < 50)
    {
        QMessageBox::critical(nullptr, "Неверное число элементов", "Количество элементов должно быть больше чем 50");

        return;
    }

    int     numCargos       = param1;
    int     populationSize  = param2;
    int     generations     = param3;
    double  crossoverProb   = (double)param4 / 100;
    double  mutationProb    = (double)param5 / 100;
    int     capacity        = param6;
    #include "ui.h"
    #include "algo.h"
    
    #include <QIcon>
    #include <QPalette>
    
    MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
    {
        CentralWidget = new QWidget(this);
    
        this->setCentralWidget(CentralWidget);
        this->setMinimumSize(500, 580);
        this->setMaximumSize(500, 580);
        this->setWindowTitle("Лабораторная работа 6");
    
        Title = new QLabel(CentralWidget);
        Title->setText("Пожалуйста, определите параметры \nпопуляции и число элементов");
        Title->setGeometry(50, 30, 400, 50);
        SetSizeForLabel(15, Title);
    
    
        LabelParam1 = new QLabel(CentralWidget);
        LabelParam1->setText("Задайте число элементов:");
        LabelParam1->setGeometry(100, 100, 250, 50);
        SetSizeForLabel(14, LabelParam1);
    
        LineEditParam1 = new QLineEdit(CentralWidget);
        LineEditParam1->setGeometry(370, 100, 50, 50);
    
    
        LabelParam2 = new QLabel(CentralWidget);
        LabelParam2->setText("Введите размер популяции:");
        LabelParam2->setGeometry(100, 160, 250, 50);
        SetSizeForLabel(14, LabelParam2);
    
        LineEditParam2 = new QLineEdit(CentralWidget);
        LineEditParam2->setGeometry(370, 160, 50, 50);
    
    
        LabelParam3 = new QLabel(CentralWidget);
        LabelParam3->setText("Введите число поколений:");
        LabelParam3->setGeometry(100, 220, 250, 50);
        SetSizeForLabel(14, LabelParam3);
    
        LineEditParam3 = new QLineEdit(CentralWidget);
        LineEditParam3->setGeometry(370, 220, 50, 50);
    
    
        LabelParam4 = new QLabel(CentralWidget);
        LabelParam4->setText("Введите вероятность кроссовера (%):");
        LabelParam4->setGeometry(30, 280, 335, 50);
        SetSizeForLabel(14, LabelParam4);
    
        LineEditParam4 = new QLineEdit(CentralWidget);
        LineEditParam4->setGeometry(370, 280, 50, 50);
    
    
        LabelParam5 = new QLabel(CentralWidget);
        LabelParam5->setText("Введите вероятность мутаций (%):");
        LabelParam5->setGeometry(30, 340, 335, 50);
        SetSizeForLabel(14, LabelParam5);
    
        LineEditParam5 = new QLineEdit(CentralWidget);
        LineEditParam5->setGeometry(370, 340, 50, 50);
    
        
        LabelParam6 = new QLabel(CentralWidget);
        LabelParam6->setText("Ограничение по итоговой сумме:");
        LabelParam6->setGeometry(30, 400, 335, 50);
        SetSizeForLabel(14, LabelParam6);
    
        LineEditParam6 = new QLineEdit(CentralWidget);
        LineEditParam6->setGeometry(370, 400, 50, 50);
    
        Start = new QPushButton(CentralWidget);
        Start->setGeometry(10, 500, 50, 50);
        Start->setIcon(QIcon("../res/run.png"));
        Start->setIconSize(Start->size());
        Start->setStyleSheet("background-color: transparent; border: none;");
        QObject::connect(Start, &QPushButton::clicked, this, &MainWindow::StartSlot);
    
        Params = new QPushButton(CentralWidget);
        Params->setText("Параметры");
        Params->setGeometry(70, 500, 133, 50);
        SetSizeForButton(12, Params);
        SetColorForButton(QColor(33, 156, 49), Params);
        QObject::connect(Params, &QPushButton::clicked, this, &MainWindow::ParamsDataShowSlot);
    
        Solutions = new QPushButton(CentralWidget);
        Solutions->setText("Решения");
        Solutions->setGeometry(213, 500, 133, 50);
        SetSizeForButton(12, Solutions);
        SetColorForButton(QColor(33, 156, 49), Solutions);
        QObject::connect(Solutions, &QPushButton::clicked, this, &MainWindow::SolutionsDataShowSlot);
    
        Table = new QPushButton(CentralWidget);
        Table->setText("Таблица");
        Table->setGeometry(356, 500, 133, 50);
        SetSizeForButton(12, Table);
        SetColorForButton(QColor(33, 156, 49), Table);
        QObject::connect(Table, &QPushButton::clicked, this, &MainWindow::TableDataShowSlot);
    }
    
    void MainWindow::SetColorForButton(QColor color, QPushButton* Button)
    {
        QPalette palette = Button->palette();
        palette.setColor(QPalette::Button, color);
        Button->setPalette(palette);
    }
    
    void MainWindow::SetSizeForLabel(int Size, QLabel* Label)
    {
        Label->setAlignment(Qt::AlignCenter);
        QFont font = Label->font();
        font.setPointSize(Size);
        Label->setFont(font);
    }
    
    void MainWindow::SetSizeForButton(int Size, QPushButton* Button)
    {
        QFont font = Button->font();
        font.setPointSize(Size);
        Button->setFont(font);
    }
    
    void MainWindow::StartSlot()
    {
        mt19937 rng((unsigned) time(0));
    
        int  param1 = std::stoi(LineEditParam1->text().toStdString());
        int  param2 = std::stoi(LineEditParam2->text().toStdString());
        int  param3 = std::stoi(LineEditParam3->text().toStdString());
        int  param4 = std::stoi(LineEditParam4->text().toStdString());
        int  param5 = std::stoi(LineEditParam5->text().toStdString());
        int  param6 = std::stoi(LineEditParam6->text().toStdString());
    
        if (param1 < 50)
        {
            QMessageBox::critical(nullptr, "Неверное число элементов", "Количество элементов должно быть больше чем 50");
    
            return;
        }
    
        int     numCargos       = param1;
        int     populationSize  = param2;
        int     generations     = param3;
        double  crossoverProb   = (double)param4 / 100;
        double  mutationProb    = (double)param5 / 100;
        int     capacity        = param6;
    
        vector<Cargo> cargos;
        for (int i = 0; i < numCargos; i++) 
        {
            Cargo c;
            c.id = i + 1;
            c.name = "Груз" + to_string(i + 1);
    
            // Генерируем диапазоны количества (например, от 1 до 10, можно варьировать)
            uniform_int_distribution<int> distMin(1, 5);
            c.minQuantity = distMin(rng);
            uniform_int_distribution<int> distMax(c.minQuantity + 1, c.minQuantity + 10);
            c.maxQuantity = distMax(rng);
    
            // Стоимость за единицу – случайное число (например, от 10 до 100)
            uniform_real_distribution<double> distCost(10.0, 100.0);
            c.unitCost = distCost(rng);
            cargos.push_back(c);
        }
        
        TableData = "";
        TableData += "\nНомер | Наименование груза | Мин.количество | Макс.количество | Стоимость ед\n";
    
        for (const Cargo &c : cargos) 
        {
            TableData += QString::number(c.id)              + (QString)"\t|\t";
            TableData += QString::fromStdString(c.name)     + (QString)"\t|\t";
            TableData += QString::number(c.minQuantity)     + (QString)"\t|\t";
            TableData += QString::number(c.maxQuantity)     + (QString)"\t|\t";
            TableData += QString::number(c.unitCost)        + (QString)"\t|\t\n";
        }
        std::cout << TableData.toStdString() << std::endl;
    
        cout << "\nНачало работы генетического алгоритма...\n";
        
        vector<Individual> population = initializePopulation(populationSize, cargos);
        
        Individual bestIndividual;
        double bestFitness = -1e9;
        
        // Основной цикл эволюции
        SolutionsData = "";
        for (int gen = 0; gen < generations; gen++) 
        {
            vector<Individual> newPopulation;
            while (newPopulation.size() < population.size())
            {
                // Отбор родителей
                Individual parent1 = tournamentSelection(population, cargos, capacity);
                Individual parent2 = tournamentSelection(population, cargos, capacity);
    
                // Кроссовер
                auto children = crossover(parent1, parent2, crossoverProb);
    
                // Мутация
                mutate(children.first, cargos, mutationProb);
                mutate(children.second, cargos, mutationProb);
                newPopulation.push_back(children.first);
                if (newPopulation.size() < population.size())
                    newPopulation.push_back(children.second);
            }
            population = newPopulation;
            
            for (const auto &ind : population) 
            {
                double f = fitness(ind, cargos, capacity);
                if (f > bestFitness) 
                {
                    bestFitness = f;
                    bestIndividual = ind;
                }
            }
            
            SolutionsData += (QString)"Поколение ";
            SolutionsData += QString::number(gen + 1);
            SolutionsData += (QString)", лучшее значение приспособленности: ";
            SolutionsData += QString::number(bestFitness);
            SolutionsData += "\n";
        }
        
        SolutionsData += (QString)"\n\nЛучшее найденное решение:\n";
        SolutionsData += (QString)"Общая стоимость: "       + QString::number(totalProfit(bestIndividual, cargos));
        SolutionsData += (QString)" | Общее количество: "   + QString::number(totalQuantity(bestIndividual));
    
        std::cout << SolutionsData.toStdString() << std::endl;
        
        ParamsData = "";
        ParamsData += (QString)"\nКлючевые параметры алгоритма:\n";
        ParamsData += (QString)"- Размер популяции: "                                           + QString::number(populationSize)   + (QString)"\n";
        ParamsData += (QString)"- Число поколений: "                                            + QString::number(generations)      + (QString)"\n";
        ParamsData += (QString)"- Вероятность кроссовера: "                                     + QString::number(crossoverProb)    + (QString)"\n";
        ParamsData += (QString)"- Вероятность мутации: "                                        + QString::number(mutationProb)     + (QString)"\n";
        ParamsData += (QString)"- Грузоподъемность (ограничение по суммарному количеству): "    + QString::number(capacity)         + (QString)"\n";
    
        std::cout << ParamsData.toStdString() << std::endl;
    }
    
    void MainWindow::TableDataShowSlot()
    {
        if (TableData != "")        QMessageBox::information(nullptr, "Таблица данных", TableData);
        else                        QMessageBox::information(nullptr, "Таблица данных", "Данных о таблице пока нет\n\nНажмите на кнопку старт");
    }
    
    void MainWindow::ParamsDataShowSlot()
    {
        if (ParamsData != "")       QMessageBox::information(nullptr, "Параметры", ParamsData);
        else                        QMessageBox::information(nullptr, "Параметры", "Параметры пока не заданы\n\nНажмите на кнопку старт");
    }
    
    void MainWindow::SolutionsDataShowSlot()
    {
        if (SolutionsData != "")    QMessageBox::information(nullptr, "Данные о решениях", SolutionsData);
        else                        QMessageBox::information(nullptr, "Данные о решениях", "Решений нет\n\nНажмите на кнопку старт");
    }#include "ui.h"
#include "algo.h"

#include <QIcon>
#include <QPalette>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    CentralWidget = new QWidget(this);

    this->setCentralWidget(CentralWidget);
    this->setMinimumSize(500, 580);
    this->setMaximumSize(500, 580);
    this->setWindowTitle("Лабораторная работа 6");

    Title = new QLabel(CentralWidget);
    Title->setText("Пожалуйста, определите параметры \nпопуляции и число элементов");
    Title->setGeometry(50, 30, 400, 50);
    SetSizeForLabel(15, Title);


    LabelParam1 = new QLabel(CentralWidget);
    LabelParam1->setText("Задайте число элементов:");
    LabelParam1->setGeometry(100, 100, 250, 50);
    SetSizeForLabel(14, LabelParam1);

    LineEditParam1 = new QLineEdit(CentralWidget);
    LineEditParam1->setGeometry(370, 100, 50, 50);


    LabelParam2 = new QLabel(CentralWidget);
    LabelParam2->setText("Введите размер популяции:");
    LabelParam2->setGeometry(100, 160, 250, 50);
    SetSizeForLabel(14, LabelParam2);

    LineEditParam2 = new QLineEdit(CentralWidget);
    LineEditParam2->setGeometry(370, 160, 50, 50);


    LabelParam3 = new QLabel(CentralWidget);
    LabelParam3->setText("Введите число поколений:");
    LabelParam3->setGeometry(100, 220, 250, 50);
    SetSizeForLabel(14, LabelParam3);

    LineEditParam3 = new QLineEdit(CentralWidget);
    LineEditParam3->setGeometry(370, 220, 50, 50);


    LabelParam4 = new QLabel(CentralWidget);
    LabelParam4->setText("Введите вероятность кроссовера (%):");
    LabelParam4->setGeometry(30, 280, 335, 50);
    SetSizeForLabel(14, LabelParam4);

    LineEditParam4 = new QLineEdit(CentralWidget);
    LineEditParam4->setGeometry(370, 280, 50, 50);


    LabelParam5 = new QLabel(CentralWidget);
    LabelParam5->setText("Введите вероятность мутаций (%):");
    LabelParam5->setGeometry(30, 340, 335, 50);
    SetSizeForLabel(14, LabelParam5);

    LineEditParam5 = new QLineEdit(CentralWidget);
    LineEditParam5->setGeometry(370, 340, 50, 50);

    
    LabelParam6 = new QLabel(CentralWidget);
    LabelParam6->setText("Ограничение по итоговой сумме:");
    LabelParam6->setGeometry(30, 400, 335, 50);
    SetSizeForLabel(14, LabelParam6);

    LineEditParam6 = new QLineEdit(CentralWidget);
    LineEditParam6->setGeometry(370, 400, 50, 50);

    Start = new QPushButton(CentralWidget);
    Start->setGeometry(10, 500, 50, 50);
    Start->setIcon(QIcon("../res/run.png"));
    Start->setIconSize(Start->size());
    Start->setStyleSheet("background-color: transparent; border: none;");
    QObject::connect(Start, &QPushButton::clicked, this, &MainWindow::StartSlot);

    Params = new QPushButton(CentralWidget);
    Params->setText("Параметры");
    Params->setGeometry(70, 500, 133, 50);
    SetSizeForButton(12, Params);
    SetColorForButton(QColor(33, 156, 49), Params);
    QObject::connect(Params, &QPushButton::clicked, this, &MainWindow::ParamsDataShowSlot);

    Solutions = new QPushButton(CentralWidget);
    Solutions->setText("Решения");
    Solutions->setGeometry(213, 500, 133, 50);
    SetSizeForButton(12, Solutions);
    SetColorForButton(QColor(33, 156, 49), Solutions);
    QObject::connect(Solutions, &QPushButton::clicked, this, &MainWindow::SolutionsDataShowSlot);

    Table = new QPushButton(CentralWidget);
    Table->setText("Таблица");
    Table->setGeometry(356, 500, 133, 50);
    SetSizeForButton(12, Table);
    SetColorForButton(QColor(33, 156, 49), Table);
    QObject::connect(Table, &QPushButton::clicked, this, &MainWindow::TableDataShowSlot);
}

void MainWindow::SetColorForButton(QColor color, QPushButton* Button)
{
    QPalette palette = Button->palette();
    palette.setColor(QPalette::Button, color);
    Button->setPalette(palette);
}

void MainWindow::SetSizeForLabel(int Size, QLabel* Label)
{
    Label->setAlignment(Qt::AlignCenter);
    QFont font = Label->font();
    font.setPointSize(Size);
    Label->setFont(font);
}

void MainWindow::SetSizeForButton(int Size, QPushButton* Button)
{
    QFont font = Button->font();
    font.setPointSize(Size);
    Button->setFont(font);
}

void MainWindow::StartSlot()
{
    mt19937 rng((unsigned) time(0));

    int  param1 = std::stoi(LineEditParam1->text().toStdString());
    int  param2 = std::stoi(LineEditParam2->text().toStdString());
    int  param3 = std::stoi(LineEditParam3->text().toStdString());
    int  param4 = std::stoi(LineEditParam4->text().toStdString());
    int  param5 = std::stoi(LineEditParam5->text().toStdString());
    int  param6 = std::stoi(LineEditParam6->text().toStdString());

    if (param1 < 50)
    {
        QMessageBox::critical(nullptr, "Неверное число элементов", "Количество элементов должно быть больше чем 50");

        return;
    }

    int     numCargos       = param1;
    int     populationSize  = param2;
    int     generations     = param3;
    double  crossoverProb   = (double)param4 / 100;
    double  mutationProb    = (double)param5 / 100;
    int     capacity        = param6;

    vector<Cargo> cargos;
    for (int i = 0; i < numCargos; i++) 
    {
        Cargo c;
        c.id = i + 1;
        c.name = "Груз" + to_string(i + 1);

        // Генерируем диапазоны количества (например, от 1 до 10, можно варьировать)
        uniform_int_distribution<int> distMin(1, 5);
        c.minQuantity = distMin(rng);

        uniform_int_distribution<int> distMax(c.minQuantity + 1, c.minQuantity + 10);
        c.maxQuantity = distMax(rng);

        // Стоимость за единицу – случайное число (например, от 10 до 100)
        uniform_real_distribution<double> distCost(10.0, 100.0);
        c.unitCost = distCost(rng);
        cargos.push_back(c);
    }
    
    TableData = "";
    TableData += "\nНомер | Наименование груза | Мин.количество | Макс.количество | Стоимость ед\n";

    for (const Cargo &c : cargos) 
    {
        TableData += QString::number(c.id)              + (QString)"\t|\t";
        TableData += QString::fromStdString(c.name)     + (QString)"\t|\t";
        TableData += QString::number(c.minQuantity)     + (QString)"\t|\t";
        TableData += QString::number(c.maxQuantity)     + (QString)"\t|\t";
        TableData += QString::number(c.unitCost)        + (QString)"\t|\t\n";
    }
    std::cout << TableData.toStdString() << std::endl;

    cout << "\nНачало работы генетического алгоритма...\n";
    
    vector<Individual> population = initializePopulation(populationSize, cargos);
    
    Individual bestIndividual;
    double bestFitness = -1e9;
    
    // Основной цикл эволюции
    SolutionsData = "";
    for (int gen = 0; gen < generations; gen++) 
    {
        vector<Individual> newPopulation;
        while (newPopulation.size() < population.size())
        {
            // Отбор родителей
            Individual parent1 = tournamentSelection(population, cargos, capacity);
            Individual parent2 = tournamentSelection(population, cargos, capacity);

            // Кроссовер
            auto children = crossover(parent1, parent2, crossoverProb);

            // Мутация
            mutate(children.first, cargos, mutationProb);
            mutate(children.second, cargos, mutationProb);
            newPopulation.push_back(children.first);
            if (newPopulation.size() < population.size())
                newPopulation.push_back(children.second);
        }
        population = newPopulation;
        
        for (const auto &ind : population) 
        {
            double f = fitness(ind, cargos, capacity);
            if (f > bestFitness) 
            {
                bestFitness = f;
                bestIndividual = ind;
            }
        }
        
        SolutionsData += (QString)"Поколение ";
        SolutionsData += QString::number(gen + 1);
        SolutionsData += (QString)", значение приспособленности: ";
        SolutionsData += QString::number(bestFitness);
        SolutionsData += "\n";
    }
    
    SolutionsData += (QString)"\n\nЛучшее найденное решение:\n";
    SolutionsData += (QString)"Общая стоимость: "       + QString::number(totalProfit(bestIndividual, cargos));
    SolutionsData += (QString)" | Общее количество: "   + QString::number(totalQuantity(bestIndividual));

    std::cout << SolutionsData.toStdString() << std::endl;
    
    ParamsData = "";
    ParamsData += (QString)"\nКлючевые параметры алгоритма:\n";
    ParamsData += (QString)"- Размер популяции: "                                           + QString::number(populationSize)   + (QString)"\n";
    ParamsData += (QString)"- Число поколений: "                                            + QString::number(generations)      + (QString)"\n";
    ParamsData += (QString)"- Вероятность кроссовера: "                                     + QString::number(crossoverProb)    + (QString)"\n";
    ParamsData += (QString)"- Вероятность мутации: "                                        + QString::number(mutationProb)     + (QString)"\n";
    ParamsData += (QString)"- Грузоподъемность (ограничение по суммарному количеству): "    + QString::number(capacity)         + (QString)"\n";

    std::cout << ParamsData.toStdString() << std::endl;
}

void MainWindow::TableDataShowSlot()
{
    if (TableData != "")        QMessageBox::information(nullptr, "Таблица данных", TableData);
    else                        QMessageBox::information(nullptr, "Таблица данных", "Данных о таблице пока нет\n\nНажмите на кнопку старт");
}

void MainWindow::ParamsDataShowSlot()
{
    if (ParamsData != "")       QMessageBox::information(nullptr, "Параметры", ParamsData);
    else                        QMessageBox::information(nullptr, "Параметры", "Параметры пока не заданы\n\nНажмите на кнопку старт");
}

void MainWindow::SolutionsDataShowSlot()
{
    if (SolutionsData != "")    QMessageBox::information(nullptr, "Данные о решениях", SolutionsData);
    else                        QMessageBox::information(nullptr, "Данные о решениях", "Решений нет\n\nНажмите на кнопку старт");
}
    vector<Cargo> cargos;
    for (int i = 0; i < numCargos; i++) 
    {
        Cargo c;
        c.id = i + 1;
        c.name = "Груз" + to_string(i + 1);

        // Генерируем диапазоны количества (например, от 1 до 10, можно варьировать)
        uniform_int_distribution<int> distMin(1, 5);
        c.minQuantity = distMin(rng);
        uniform_int_distribution<int> distMax(c.minQuantity + 1, c.minQuantity + 10);
        c.maxQuantity = distMax(rng);

        // Стоимость за единицу – случайное число (например, от 10 до 100)
        uniform_real_distribution<double> distCost(10.0, 100.0);
        c.unitCost = distCost(rng);
        cargos.push_back(c);
    }
    
    TableData = "";
    TableData += "\nНомер | Наименование груза | Мин.количество | Макс.количество | Стоимость ед\n";

    for (const Cargo &c : cargos) 
    {
        TableData += QString::number(c.id)              + (QString)"\t|\t";
        TableData += QString::fromStdString(c.name)     + (QString)"\t|\t";
        TableData += QString::number(c.minQuantity)     + (QString)"\t|\t";
        TableData += QString::number(c.maxQuantity)     + (QString)"\t|\t";
        TableData += QString::number(c.unitCost)        + (QString)"\t|\t\n";
    }
    std::cout << TableData.toStdString() << std::endl;

    cout << "\nНачало работы генетического алгоритма...\n";
    
    vector<Individual> population = initializePopulation(populationSize, cargos);
    
    Individual bestIndividual;
    double bestFitness = -1e9;
    
    // Основной цикл эволюции
    SolutionsData = "";
    for (int gen = 0; gen < generations; gen++) 
    {
        vector<Individual> newPopulation;
        while (newPopulation.size() < population.size())
        {
            // Отбор родителей
            Individual parent1 = tournamentSelection(population, cargos, capacity);
            Individual parent2 = tournamentSelection(population, cargos, capacity);

            // Кроссовер
            auto children = crossover(parent1, parent2, crossoverProb);

            // Мутация
            mutate(children.first, cargos, mutationProb);
            mutate(children.second, cargos, mutationProb);
            newPopulation.push_back(children.first);
            if (newPopulation.size() < population.size())
                newPopulation.push_back(children.second);
        }
        population = newPopulation;
        
        for (const auto &ind : population) 
        {
            double f = fitness(ind, cargos, capacity);
            if (f > bestFitness) 
            {
                bestFitness = f;
                bestIndividual = ind;
            }
        }
        
        SolutionsData += (QString)"Поколение ";
        SolutionsData += QString::number(gen + 1);
        SolutionsData += (QString)", лучшее значение приспособленности: ";
        SolutionsData += QString::number(bestFitness);
        SolutionsData += "\n";
    }
    
    SolutionsData += (QString)"\n\nЛучшее найденное решение:\n";
    SolutionsData += (QString)"Общая стоимость: "       + QString::number(totalProfit(bestIndividual, cargos));
    SolutionsData += (QString)" | Общее количество: "   + QString::number(totalQuantity(bestIndividual));

    std::cout << SolutionsData.toStdString() << std::endl;
    
    ParamsData = "";
    ParamsData += (QString)"\nКлючевые параметры алгоритма:\n";
    ParamsData += (QString)"- Размер популяции: "                                           + QString::number(populationSize)   + (QString)"\n";
    ParamsData += (QString)"- Число поколений: "                                            + QString::number(generations)      + (QString)"\n";
    ParamsData += (QString)"- Вероятность кроссовера: "                                     + QString::number(crossoverProb)    + (QString)"\n";
    ParamsData += (QString)"- Вероятность мутации: "                                        + QString::number(mutationProb)     + (QString)"\n";
    ParamsData += (QString)"- Грузоподъемность (ограничение по суммарному количеству): "    + QString::number(capacity)         + (QString)"\n";

    std::cout << ParamsData.toStdString() << std::endl;
}

void MainWindow::TableDataShowSlot()
{
    if (TableData != "")        QMessageBox::information(nullptr, "Таблица данных", TableData);
    else                        QMessageBox::information(nullptr, "Таблица данных", "Данных о таблице пока нет\n\nНажмите на кнопку старт");
}

void MainWindow::ParamsDataShowSlot()
{
    if (ParamsData != "")       QMessageBox::information(nullptr, "Параметры", ParamsData);
    else                        QMessageBox::information(nullptr, "Параметры", "Параметры пока не заданы\n\nНажмите на кнопку старт");
}

void MainWindow::SolutionsDataShowSlot()
{
    if (SolutionsData != "")    QMessageBox::information(nullptr, "Данные о решениях", SolutionsData);
    else                        QMessageBox::information(nullptr, "Данные о решениях", "Решений нет\n\nНажмите на кнопку старт");
}