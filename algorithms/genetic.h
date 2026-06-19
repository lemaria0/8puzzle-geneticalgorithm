#ifndef GENETIC_H
#define GENETIC_H

#include "../core/puzzle_state.h"

#include <vector>


// Índices dos movimentos
enum Move
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

// Estrutura do indivíduo
struct Individual
{
    std::vector<int> genes;
    PuzzleState bestState;
    int stepsToBest = 0;
    double bestFitness = 0;
    bool solved = false;
};

// Calcula o fitness considerando a qualidade do estado e o custo dos movimentos
double calculateFitness(const PuzzleState& state, int steps);

// Gera um indivíduo com uma sequência válida de movimentos
Individual generateIndividual(const PuzzleState& initialState, int geneLength);

// Executa os genes de um indivíduo e encontra o melhor estado alcançado
void applyGenes(Individual& ind, const PuzzleState& initialState);

// Gera a população inicial
std::vector<Individual> generateInitialPopulation(
    int populationSize,
    int geneLength,
    int shuffleMoves
);

// Ordena população pelo menor fitness
void orderPopulation(std::vector<Individual>& population);

#endif
