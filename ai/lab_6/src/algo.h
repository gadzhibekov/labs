#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

struct Cargo 
{
    int id;
    string name;
    int minQuantity;
    int maxQuantity;
    double unitCost;
};

typedef vector<int> Individual;

const double PENALTY_FACTOR = 1000.0;

// Функция вычисления суммы выбранных единиц (будем считать, что суммарное количество = суммарный вес)
int totalQuantity(const Individual &ind);

// Функция вычисления суммарной стоимости (цель – максимизировать прибыль)
double totalProfit(const Individual &ind, const vector<Cargo>& cargos);

// Функция оценки индивида с учетом штрафа за превышение ограничений по суммарному количеству (грузоподъемности)
double fitness(const Individual &ind, const vector<Cargo>& cargos, int capacity);

// Инициализация популяции случайными индивидами, каждый ген выбирается в диапазоне [min, max]
vector<Individual> initializePopulation(int popSize, const vector<Cargo>& cargos);

// Турнирный отбор: выбираем случайно 2 индивида и возвращаем лучший
Individual tournamentSelection(const vector<Individual>& population, const vector<Cargo>& cargos, int capacity);

// Одноточечное скрещивание: выбираем случайную точку и меняем хвосты родителей
pair<Individual, Individual> crossover(const Individual& parent1, const Individual& parent2, double crossoverProb);

// Мутация: с заданной вероятностью изменить значение гена
void mutate(Individual &ind, const vector<Cargo>& cargos, double mutationProb);