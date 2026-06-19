#include "genetic.h"
#include "../core/puzzle_state.h"
#include "../core/utils.h"

#include <algorithm>
#include <cstdlib>

/*
Índice de movimentos:
0 - cima
1 - baixo
2 - esquerda
3 - direita
*/


constexpr double STEP_COST = 0.2;

double calculateFitness(const PuzzleState &state, int steps)
{
    return calculateHeuristics(state) + STEP_COST * steps;
}

Individual generateIndividual(const PuzzleState &initialState, int geneLength)
{
    Individual ind;
    PuzzleState auxState = initialState;

    while (ind.genes.size() < geneLength)
    {
        int move = generateRandomMove(auxState);

        if (applyMove(auxState, move))
            ind.genes.push_back(move);
    }

    return ind;
}

void applyGenes(Individual &ind, const PuzzleState &initialState)
{
    PuzzleState currentState = initialState;
    PuzzleState goalState = getGoalState();
    int currentSteps = 0;

    PuzzleState bestState = initialState;
    double bestFitness = calculateFitness(initialState, 0);
    int stepsToBest = 0;
    bool solved = false;

    for (int move : ind.genes)
    {
        if (!applyMove(currentState, move))
            break;

        currentSteps++;
        double currentFitness = calculateFitness(currentState, currentSteps);

        if (currentFitness < bestFitness)
        {
            bestState = currentState;
            bestFitness = currentFitness;
            stepsToBest = currentSteps;
        }

        if (currentState == goalState)
        {
            solved = true;
            break;
        }
    }

    ind.bestState = bestState;
    ind.bestFitness = bestFitness;
    ind.stepsToBest = stepsToBest;
    ind.solved = solved;
}

std::vector<Individual> generateInitialPopulation(int populationSize, int geneLength, int shuffleMoves)
{
    PuzzleState initialState = generateRandomInitial(shuffleMoves);
    std::vector<Individual> population;

    while (population.size() < populationSize)
    {
        Individual ind = generateIndividual(initialState, geneLength);
        applyGenes(ind, initialState);
        population.push_back(ind);
    }

    return population;
}

void orderPopulation(std::vector<Individual> &population)
{
    std::sort(
        population.begin(),
        population.end(),

        [](const Individual &a, const Individual &b)
        { return a.bestFitness < b.bestFitness; });
}
