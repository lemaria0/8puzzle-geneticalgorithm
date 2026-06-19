#include "genetic.h"
#include "utils.h"
#include <iostream>

/*
Índice de movimentos:
...0 cima
...1 baixo
...2 esquerda
...3 direita
*/

// Aplica a sequência de genes de um indivíduo sobre o estado inicial do tabuleiro
void applyGenes(Individual &ind, const PuzzleState &initialState)
{
    PuzzleState currentState = initialState;
    int currentSteps = 0;

    PuzzleState bestState = initialState;
    double bestFitness = calculateHeuristics(bestState);
    int stepsToBest = 0;

    for (int move : ind.genes)
    {
        if (!applyMove(currentState, move))
            break;

        currentSteps++;
        double currentFitness = calculateHeuristics(currentState) + 0.2 * currentSteps;

        if (currentFitness < bestFitness)
        {
            bestState = currentState;
            stepsToBest = currentSteps;
            bestFitness = currentFitness;
        }

        if (bestState == getGoalState())
            break;
    }
    ind.bestFitness = bestFitness;
    ind.stepsToBest = stepsToBest;
}

// Gera a população inicial com base nas quantidades de indivíduos, movimentos do genes e movimentos de embaralhamento (para geração do estado inicial)
std::vector<Individual> generateInitialPopulation(int populationSize, int geneLength, int shuffleMoves)
{
    PuzzleState initialState = generateRandomInitial(shuffleMoves);
    std::vector<Individual> population;

    while (population.size() < populationSize)
    {
        Individual ind;
        PuzzleState auxState = initialState;

        while (ind.genes.size() < geneLength)
        {
            std::vector<int> validMoves = getValidMoves(auxState);

            int index = rand() % validMoves.size();
            int move = validMoves[index];

            if (applyMove(auxState, move))
            {
                ind.genes.push_back(move);
            }
        }

        applyGenes(ind, initialState);
        population.push_back(ind);
    }

    return population;
}
