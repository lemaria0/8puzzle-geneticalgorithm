#include "genetic.h"
#include "../core/puzzle_state.h"
#include "../core/utils.h"

#include <algorithm>
#include <random>

/*
Índice de movimentos:
0 - cima, 1 - baixo, 2 - esquerda, 3 - direita
*/

constexpr double STEP_WEIGHT = 0.1;
constexpr double STAGNATION_WEIGHT = 0.3;

static std::mt19937 &getPRNG()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

double randPercent()
{
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(getPRNG());
}

static size_t randIndex(size_t max)
{
    std::uniform_int_distribution<size_t> dist(0, max - 1);
    return dist(getPRNG());
}

Individual generateIndividual(const PuzzleState &initialState, int geneLength)
{
    Individual ind;
    ind.genes.reserve(geneLength);
    PuzzleState auxState = initialState;

    while (ind.genes.size() < static_cast<size_t>(geneLength))
    {
        int move = generateRandomMove(auxState);

        if (applyMove(auxState, move))
        {
            ind.genes.push_back(static_cast<Move>(move));
        }
    }

    return ind;
}

double calculateFitness(Individual &ind, const PuzzleState &initialState)
{
    PuzzleState currentState = initialState;
    const PuzzleState goalState = getGoalState();

    int steps = 0;
    int stagnation = 0;

    ind.bestState = initialState;
    ind.stepsToBest = 0;
    ind.stagnation = 0;
    ind.bestFitness = calculateHeuristics(initialState);
    ind.solved = false;

    for (Move move : ind.genes)
    {
        if (!applyMove(currentState, static_cast<int>(move)))
        {
            stagnation++;
        }

        steps++;

        double currentFitness = calculateHeuristics(currentState) + (STEP_WEIGHT * steps) + (STAGNATION_WEIGHT * stagnation);

        if (currentFitness < ind.bestFitness)
        {
            ind.bestFitness = currentFitness;
            ind.bestState = currentState;
            ind.stepsToBest = steps;
            ind.stagnation = stagnation;
        }

        if (calculateHeuristics(ind.bestState) == 0)
        {
            ind.solved = true;
            break;
        }
    }

    return ind.bestFitness;
}

std::vector<Individual> generateInitialPopulation(const PuzzleState &initialState, int populationSize, int geneLength)
{
    std::vector<Individual> population;
    population.reserve(populationSize);

    while (population.size() < static_cast<size_t>(populationSize))
    {
        Individual ind = generateIndividual(initialState, geneLength);
        calculateFitness(ind, initialState);
        population.push_back(std::move(ind));
    }

    orderPopulation(population);
    return population;
}

void orderPopulation(std::vector<Individual> &population)
{
    std::sort(population.begin(), population.end(), [](const Individual &a, const Individual &b)
    { return a.bestFitness < b.bestFitness; });
}

std::vector<Individual> elitismSelection(const std::vector<Individual> &population, double elitismRate)
{
    size_t eliteSize = static_cast<size_t>(elitismRate * population.size());
    return std::vector<Individual>(population.begin(), population.begin() + eliteSize);
}

Individual tournamentSelection(const std::vector<Individual> &population)
{
    size_t roundSize = std::max(size_t(2), static_cast<size_t>(population.size() * 0.05));
    Individual winner = population[randIndex(population.size())];

    for (size_t i = 1; i < roundSize; i++)
    {
        const Individual &candidate = population[randIndex(population.size())];
        if (candidate.bestFitness < winner.bestFitness)
        {
            winner = candidate;
        }
    }

    return winner;
}

std::pair<Individual, Individual> crossover(const Individual &p1, const Individual &p2, const PuzzleState &initialState)
{
    Individual c1, c2;
    size_t geneSize = p1.genes.size();

    if (geneSize == 0)
        return {c1, c2};

    c1.genes.reserve(geneSize);
    c2.genes.reserve(geneSize);

    size_t crossoverIndex = randIndex(geneSize);

    for (size_t i = 0; i < geneSize; i++)
    {
        if (i < crossoverIndex)
        {
            c1.genes.push_back(p1.genes[i]);
            c2.genes.push_back(p2.genes[i]);
        }
        else
        {
            c1.genes.push_back(p2.genes[i]);
            c2.genes.push_back(p1.genes[i]);
        }
    }

    calculateFitness(c1, initialState);
    calculateFitness(c2, initialState);

    return {c1, c2};
}

void mutation(Individual &ind, double mutationRate, const PuzzleState &initialState)
{
    PuzzleState currentState = initialState;
    bool mutated = false;

    for (size_t i = 0; i < ind.genes.size(); i++)
    {
        if (mutated)
        {
            ind.genes[i] = static_cast<Move>(generateRandomMove(currentState));
        }
        else if (randPercent() < mutationRate)
        {
            ind.genes[i] = static_cast<Move>(generateRandomMove(currentState));
            mutated = true;
        }

        applyMove(currentState, static_cast<int>(ind.genes[i]));
    }

    if (mutated)
    {
        calculateFitness(ind, initialState);
    }
}

std::vector<Individual> nextGeneration(const std::vector<Individual> &population, const PuzzleState &initialState, double elitismRate, double crossoverRate, double mutationRate)
{
    std::vector<Individual> nextGen;
    size_t targetSize = population.size();
    nextGen.reserve(targetSize);

    auto elite = elitismSelection(population, elitismRate);
    nextGen.insert(nextGen.end(), elite.begin(), elite.end());

    size_t crossoverLimit = nextGen.size() + static_cast<size_t>(crossoverRate * targetSize);
    size_t geneSize = population[0].genes.size();
    int maxStagnationAllowed = std::max(2, static_cast<int>(0.1 * geneSize));

    while (nextGen.size() < crossoverLimit && nextGen.size() < targetSize)
    {
        Individual p1 = tournamentSelection(population);
        Individual p2 = tournamentSelection(population);

        auto [child1, child2] = crossover(p1, p2, initialState);

        if (child1.stagnation <= maxStagnationAllowed && nextGen.size() < crossoverLimit)
        {
            nextGen.push_back(std::move(child1));
        }
        if (child2.stagnation <= maxStagnationAllowed && nextGen.size() < crossoverLimit)
        {
            nextGen.push_back(std::move(child2));
        }
    }

    while (nextGen.size() < targetSize)
    {
        Individual clone = tournamentSelection(population);
        mutation(clone, mutationRate, initialState);
        nextGen.push_back(std::move(clone));
    }

    orderPopulation(nextGen);
    return nextGen;
}

GeneticResult runGeneticAlgorithm(const PuzzleState &initialState, int populationSize, int geneLength, int maxGenerations, double elitismRate, double crossoverRate, double mutationRate)
{
    std::vector<Individual> population = generateInitialPopulation(initialState, populationSize, geneLength);
    Individual bestInitial = population[0];

    int generation = 0;
    bool solved = population[0].solved;
    double bestFitnessHistoric = population[0].bestFitness;

    int stagnantGenerationsCount = 0;
    const int MAX_STAGNANT_GENERATIONS = std::max(10, static_cast<int>(maxGenerations * 0.1));

    while (generation < maxGenerations && stagnantGenerationsCount < MAX_STAGNANT_GENERATIONS)
    {
        population = nextGeneration(population, initialState, elitismRate, crossoverRate, mutationRate);
        generation++;

        if (population[0].bestFitness < bestFitnessHistoric)
        {
            bestFitnessHistoric = population[0].bestFitness;
            stagnantGenerationsCount = 0;
        }
        else
        {
            stagnantGenerationsCount++;
        }

        if (population[0].solved || calculateHeuristics(population[0].bestState) == 0)
        {
            solved = true;
        }
    }

    GeneticResult result;
    result.bestInitial = std::move(bestInitial);
    result.bestFinal = population[0];
    result.totalGenerations = generation;
    result.solved = solved;

    return result;
}
