#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H

#include <vector>


// Movimentos possíveis do vazio
enum Move
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

struct PuzzleState
{
    int board[3][3]{};
    int emptyRow = 0;
    int emptyCol = 0;
    bool operator==(const PuzzleState& other) const;
};

// Cria o estado objetivo
PuzzleState getGoalState();

// Gera um estado inicial solucionável a partir do objetivo
PuzzleState generateRandomInitial(int shuffles);

// Gera um movimento aleatório válido para o estado atual
int generateRandomMove(const PuzzleState& state);

// Aplica um movimento ao estado atual
bool applyMove(PuzzleState& state, int move);

// Retorna movimentos possíveis para o estado atual
std::vector<int> getValidMoves(const PuzzleState& state);

#endif // PUZZLE_STATE_H
