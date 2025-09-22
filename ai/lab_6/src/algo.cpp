#include "algo.h"

mt19937 rng((unsigned) time(0));

int totalQuantity(const Individual &ind) 
{
    int sum = 0;
    for (int qty : ind) 
    {
        sum += qty;
    }

    return sum;
}

double totalProfit(const Individual &ind, const vector<Cargo>& cargos) 
{
    double profit = 0.0;
    for (size_t i = 0; i < cargos.size(); i++) 
    {
        profit += ind[i] * cargos[i].unitCost;
    }

    return profit;
}

double fitness(const Individual &ind, const vector<Cargo>& cargos, int capacity) 
{
    int quantity = totalQuantity(ind);
    double profit = totalProfit(ind, cargos);

    if (quantity > capacity) 
    {
        double penalty = (quantity - capacity) * PENALTY_FACTOR;
        return profit - penalty;
    }

    return profit;
}

vector<Individual> initializePopulation(int popSize, const vector<Cargo>& cargos) 
{
    vector<Individual> population;

    for (int i = 0; i < popSize; i++) 
    {
        Individual ind;
        for (const Cargo &c : cargos) {
            uniform_int_distribution<int> dist(c.minQuantity, c.maxQuantity);
            ind.push_back(dist(rng));
        }
        population.push_back(ind);
    }

    return population;
}

Individual tournamentSelection(const vector<Individual>& population, const vector<Cargo>& cargos, int capacity) 
{
    uniform_int_distribution<int> dist(0, population.size() - 1);
    int i1 = dist(rng);
    int i2 = dist(rng);

    if (fitness(population[i1], cargos, capacity) > fitness(population[i2], cargos, capacity))
        return population[i1];
    else
        return population[i2];
}

pair<Individual, Individual> crossover(const Individual& parent1, const Individual& parent2, double crossoverProb) 
{
    uniform_real_distribution<double> probability(0.0, 1.0);

    if (probability(rng) > crossoverProb) 
    {
        return {parent1, parent2};
    }

    int size = parent1.size();
    uniform_int_distribution<int> pointDist(1, size - 1);
    int cp = pointDist(rng);
    
    Individual child1 = parent1, child2 = parent2;
    
    for (int i = cp; i < size; i++) 
    {
        swap(child1[i], child2[i]);
    }

    return {child1, child2};
}

void mutate(Individual &ind, const vector<Cargo>& cargos, double mutationProb) 
{
    uniform_real_distribution<double> probability(0.0, 1.0)
    ;
    for (size_t i = 0; i < ind.size(); i++) 
    {

        if (probability(rng) < mutationProb) {
            uniform_int_distribution<int> dist(cargos[i].minQuantity, cargos[i].maxQuantity);
            ind[i] = dist(rng);
        }
    }
}