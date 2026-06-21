#ifndef GENETIC_H
#define GENETIC_H

#include "../core/puzzle_state.h"
#include <vector>
#include <utility>

// Estrutura do indivíduo
struct Individual
{
    std::vector<Move> genes;

    PuzzleState bestState;
    int stepsToBest = 0;
    int stagnation = 0;
    double bestFitness = 0.0;
    bool solved = false;
};

// Estrutura do resultado do Algoritmo Genético
struct GeneticResult 
{
    Individual bestInitial;
    Individual bestFinal;
    int totalGenerations = 0;
    bool solved = false;
};

// --- FUNÇÕES ESTRUTURAIS ---

// Gera um indivíduo com uma sequência válida de movimentos
Individual generateIndividual(const PuzzleState &initialState, int geneLength);

// Calcula o fitness de um indivíduo considerando a qualidade dos genes
double calculateFitness(Individual &ind, const PuzzleState &initialState);

// Gera a população inicial a partir de um estado do quebra-cabeça
std::vector<Individual> generateInitialPopulation(const PuzzleState &initialState, int populationSize, int geneLength);

// Ordena a população pelo menor fitness (ordem crescente)
void orderPopulation(std::vector<Individual> &population);


// --- OPERADORES GENÉTICOS E SELEÇÃO ---

// Seleção por Elitismo: Retorna os melhores indivíduos da geração
std::vector<Individual> elitismSelection(const std::vector<Individual> &population, double elitismRate);

// Seleção por Torneio: Retorna o vencedor de uma disputa amostral
Individual tournamentSelection(const std::vector<Individual> &population);

// Cruzamento (Crossover): Combina dois pais e gera um par de filhos
std::pair<Individual, Individual> crossover(const Individual &p1, const Individual &p2, const PuzzleState &initialState);

// Mutação Reconstrutiva: Altera genes aleatoriamente e reconstrói a cauda de movimentos
void mutation(Individual &ind, double mutationRate, const PuzzleState &initialState);


// --- ORQUESTRADORES DE LOOP ---

// Cria a próxima geração aplicando Elite, Crossover e Mutação
std::vector<Individual> nextGeneration(const std::vector<Individual> &population, const PuzzleState &initialState, double elitismRate, double crossoverRate, double mutationRate);

// Função principal que executa todo o ciclo evolutivo do Algoritmo Genético
GeneticResult runGeneticAlgorithm(const PuzzleState &initialState, int populationSize, int geneLength, int maxGenerations, double elitismRate, double crossoverRate, double mutationRate);

#endif // GENETIC_H
