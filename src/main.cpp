#include "core/puzzle_state.h"
#include "core/utils.h"
#include "algorithms/genetic.h"

#include <iostream>

void printBoard(const PuzzleState &state)
{
    std::cout << "+---+---+---+\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            if (state.board[i][j] == 0)
                std::cout << "  | ";
            else
                std::cout << state.board[i][j] << " | ";
        }
        std::cout << "\n+---+---+---+\n";
    }
}

int main()
{
    std::cout << "Gerando tabuleiro inicial...\n";
    PuzzleState initialState = generateRandomInitial(30);

    std::cout << "\n--- TABULEIRO INICIAL GENERADO ---\n";
    printBoard(initialState);

    int populationSize = 100;
    int geneLength = 50;
    int maxGenerations = 1000;
    double elitismRate = 0.10;
    double crossoverRate = 0.30;
    double mutationRate = 0.02;

    std::cout << "\nExecutando o Algoritmo Genetico...\n";
    GeneticResult result = runGeneticAlgorithm(
        initialState, populationSize, geneLength, maxGenerations, 
        elitismRate, crossoverRate, mutationRate
    );

    std::cout << "\n=========================================\n";
    std::cout << "         RELATORIO DE EXECUCAO           \n";
    std::cout << "=========================================\n";
    std::cout << "Geracoes computadas : " << result.totalGenerations << "\n";
    std::cout << "Fitness Inicial     : " << result.bestInitial.bestFitness << "\n";
    std::cout << "Fitness Final       : " << result.bestFinal.bestFitness << "\n";
    std::cout << "Status do Objetivo  : " << (result.solved ? "SUCESSO (Resolvido!)" : "FALHA (Nao resolvido)") << "\n";
    std::cout << "Passos ate a meta   : " << result.bestFinal.stepsToBest << "\n";
    std::cout << "Estagnacoes no vetor: " << result.bestFinal.stagnation << "\n";
    std::cout << "=========================================\n";

    std::cout << "\n--- MELHOR ESTADO ALCANCADO PELO INDIVIDUO FINAL ---\n";
    printBoard(result.bestFinal.bestState);
    
    std::cout << "Distancia Heuristica ate o Objetivo: " << calculateHeuristics(result.bestFinal.bestState) << "\n";
    std::cout << "=========================================\n";

    return 0;
}
