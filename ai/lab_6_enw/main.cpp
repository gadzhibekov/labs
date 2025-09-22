#include <iostream>
 #include <vector>
 #include <random>
 #include <algorithm>
 #include <numeric>
 #include <QtWidgets>
 #include <QTableWidget>
 #include <QLineEdit>
 #include <QPushButton>
 #include <QVBoxLayout>
 #include <QLabel>
 ​
 // Структура для представления продукта
 struct Product {
  std::string name;
  int minQuantity;
  int maxQuantity;
  double cost;
 };
 ​
 // Функция для генерации случайной популяции
 std::vector<std::vector<int>> generatePopulation(int populationSize, int productCount, const std::vector<Product>& products) {
  std::vector<std::vector<int>> population(populationSize, std::vector<int>(productCount));
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int i = 0; i < populationSize; ++i) {
  for (int j = 0; j < productCount; ++j) {
  std::uniform_int_distribution<> distrib(products[j].minQuantity, products[j].maxQuantity);
  population[i][j] = distrib(gen);
  }
  }
  return population;
 }
 ​
 // Функция для оценки приспособленности особи
 double calculateFitness(const std::vector<int>& individual, const std::vector<Product>& products, double budget) {
  double totalCost = 0.0;
  for (size_t i = 0; i < individual.size(); ++i) {
  totalCost += individual[i] * products[i].cost;
  }
 ​
  // Приспособленность обратно пропорциональна отклонению от бюджета
  if (totalCost <= budget) {
  return 1.0 - (totalCost / budget); // Чем ближе к бюджету, тем лучше
  } else {
  return 0.0; // Если превышает бюджет, приспособленность равна 0
  }
 }
 ​
 // Функция для выполнения кроссовера (скрещивания)
 std::pair<std::vector<int>, std::vector<int>> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, parent1.size() - 1);
  int crossoverPoint = distrib(gen);
 ​
  std::vector<int> child1 = parent1;
  std::vector<int> child2 = parent2;
 ​
  for (size_t i = crossoverPoint; i < parent1.size(); ++i) {
  child1[i] = parent2[i];
  child2[i] = parent1[i];
  }
 ​
  return std::make_pair(child1, child2);
 }
 ​
 // Функция для выполнения мутации
 void mutate(std::vector<int>& individual, const std::vector<Product>& products, double mutationRate) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> distrib(0.0, 1.0);
 ​
  for (size_t i = 0; i < individual.size(); ++i) {
  if (distrib(gen) < mutationRate) {
  std::uniform_int_distribution<> quantityDistrib(products[i].minQuantity, products[i].maxQuantity);
  individual[i] = quantityDistrib(gen);
  }
  }
 }
 ​
 // Основная функция генетического алгоритма
 std::vector<int> geneticAlgorithm(const std::vector<Product>& products, double budget,
  int populationSize = 100, double mutationRate = 0.01, int generations = 100) {
  int productCount = products.size();
  std::vector<std::vector<int>> population = generatePopulation(populationSize, productCount, products);
 ​
  std::vector<int> bestIndividual;
  double bestFitness = 0.0;
 ​
  for (int generation = 0; generation < generations; ++generation) {
  // Оценка приспособленности каждой особи
  std::vector<double> fitnessValues(populationSize);
  for (int i = 0; i < populationSize; ++i) {
  fitnessValues[i] = calculateFitness(population[i], products, budget);
  if (fitnessValues[i] > bestFitness) {
  bestFitness = fitnessValues[i];
  bestIndividual = population[i];
  }
  }
 ​
  // Селекция (турнирный отбор)
  std::vector<std::vector<int>> newPopulation;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, populationSize - 1);
  for (int i = 0; i < populationSize; ++i) {
  int idx1 = distrib(gen);
  int idx2 = distrib(gen);
  newPopulation.push_back(fitnessValues[idx1] > fitnessValues[idx2] ? population[idx1] : population[idx2]);
  }
 ​
  // Кроссовер и мутация
  for (int i = 0; i < populationSize; i += 2) {
  if (i + 1 < populationSize) {
  auto children = crossover(newPopulation[i], newPopulation[i + 1]);
  newPopulation[i] = children.first;
  newPopulation[i + 1] = children.second;
  mutate(newPopulation[i], products, mutationRate);
  mutate(newPopulation[i + 1], products, mutationRate);
  }
  }
 ​
  population = newPopulation;
  }
 ​
  return bestIndividual;
 }
 ​
 // Класс главного окна приложения
 class MainWindow : public QWidget {
  Q_OBJECT
 public:
  MainWindow() {
  // Создание элементов интерфейса
  productTable = new QTableWidget(50, 5); // 50 продуктов, 5 столбцов
  productTable->setHorizontalHeaderLabels({"Наименование", "Мин. кол-во", "Макс. кол-во", "Цена за ед.", "Кол-во для закупки"});
  budgetLabel = new QLabel("Бюджет:");
  budgetInput = new QLineEdit;
  runButton = new QPushButton("Запустить");
  resultLabel = new QLabel;
 ​
  // Установка размеров столбцов
  productTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
  productTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
  productTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
  productTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
  productTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
 ​
  // Заполнение таблицы примерами данных
  for (int i = 0; i < 50; ++i) {
  productTable->setItem(i, 0, new QTableWidgetItem("Продукт " + QString::number(i + 1)));
  productTable->setItem(i, 1, new QTableWidgetItem(QString::number(1)));
  productTable->setItem(i, 2, new QTableWidgetItem(QString::number(10)));
  productTable->setItem(i, 3, new QTableWidgetItem(QString::number(i % 10 + 1 + 0.99)));
  productTable->setItem(i, 4, new QTableWidgetItem("0")); // Изначально количество для закупки равно 0
  }
 ​
  // Создание layout
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(productTable);
  layout->addWidget(budgetLabel);
  layout->addWidget(budgetInput);
  layout->addWidget(runButton);
  layout->addWidget(resultLabel);
 ​
  // Установка layout в главное окно
  setLayout(layout);
  setWindowTitle("Генетический алгоритм закупки продуктов");
 ​
  // Подключение сигнала нажатия кнопки к слоту
  connect(runButton, &QPushButton::clicked, this, &MainWindow::runGeneticAlgorithm);
  }
 ​
 private slots:
  void runGeneticAlgorithm() {
  // Считывание данных из таблицы и поля ввода бюджета
  std::vector<Product> products(50);
  for (int i = 0; i < 50; ++i) {
  products[i].name = productTable->item(i, 0)->text().toStdString();
  products[i].minQuantity = productTable->item(i, 1)->text().toInt();
  products[i].maxQuantity = productTable->item(i, 2)->text().toInt();
  products[i].cost = productTable->item(i, 3)->text().toDouble();
  }
  double budget = budgetInput->text().toDouble();
 ​
  // Запуск генетического алгоритма
  std::vector<int> result = geneticAlgorithm(products, budget);
 ​
  // Вывод результатов в таблицу
  for (int i = 0; i < 50; ++i) {
  productTable->item(i, 4)->setText(QString::number(result[i]));
  }
 ​
  // Расчет и вывод итоговой стоимости
  double totalCost = 0.0;
  for (int i = 0; i < 50; ++i) {
  totalCost += result[i] * products[i].cost;
  }
  resultLabel->setText("Итоговая стоимость: " + QString::number(totalCost));
  }
 ​
 private:
  QTableWidget *productTable;
  QLabel *budgetLabel;
  QLineEdit *budgetInput;
  QPushButton *runButton;
  QLabel *resultLabel;
 };
 ​
 int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow window;
  window.show();
  return app.exec();
 }
 ​
 #include "main.moc" // Необходимо для работы слотов Qt