#include "genetic.h"
#include "../core/utils.h"

/*
Índice de movimentos:
    0 cima
    1 baixo
    2 esquerda
    3 direita
*/

// Aplica um movimento ao estado atual do tabuleiro
bool applyMove(PuzzleState& state, int move) {
    int dr = state.emptyRow;
    int dc = state.emptyCol;

    if (move == 0) dr--;
    else if (move == 1) dr++;
    else if (move == 2) dc--;
    else if (move == 3) dc++;

    if (dr < 0 || dr >= 3 || dc < 0 || dc >= 3) return false;
    std::swap(state.board[state.emptyRow][state.emptyCol], state.board[dr][dc]);
    state.emptyRow = dr;
    state.emptyCol = dc;
    return true;
}

// Aplica a sequência de genes de um indivíduo ao estado inicial do tabuleiro
void applyGenes(Individual& ind, const PuzzleState& initialState) {
    PuzzleState currentState = initialState;

    for (int move : ind.genes) {
        if (!applyMove(currentState, move)) break;
    }

    ind.bestState = currentState;
}

std::vector<Individual> generateInitialPopulation(int populationSize, int geneLength, int shuffleMoves) {
    std::vector<Individual> population;

    

    return population;
}
