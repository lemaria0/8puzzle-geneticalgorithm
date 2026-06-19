#include <iostream>
#include <vector>
// #include <GLFW/glfw3.h>
#include "core/puzzle_state.h"
#include "algorithms/genetic.h"
#include "render/renderer.h"

extern PuzzleState generateRandomInitial(int shuffles);
extern int calculateManhattan(const PuzzleState &s);

// Imprime o estado do tabuleiro (para depuração)
void printState(const PuzzleState &state) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << state.board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Posicao vazia: (" << state.emptyRow << ", " << state.emptyCol << ")" << std::endl;
}

int main() {
    PuzzleState puzzle8;

    puzzle8.board[0][0] = 1; puzzle8.board[0][1] = 2; puzzle8.board[0][2] = 3;
    puzzle8.board[1][0] = 4; puzzle8.board[1][1] = 5; puzzle8.board[1][2] = 6;
    puzzle8.board[2][0] = 0; puzzle8.board[2][1] = 7; puzzle8.board[2][2] = 8;

    puzzle8.emptyRow = 2;
    puzzle8.emptyCol = 0;

    printState(puzzle8);
    applyMove(puzzle8, 3);
    printState(puzzle8);

    return 0;
}
