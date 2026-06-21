#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H

#include <vector>

// Índice de movimentos das peças
enum Move : int
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

// Estrutura do 8-puzzle
struct PuzzleState
{
    int board[3][3]{};
    int emptyRow = 0;
    int emptyCol = 0;
    
    bool operator==(const PuzzleState& other) const;
};

// Gera o estado objetivo clássico do 8-puzzle (1 a 8 com o 0 no fim)
PuzzleState getGoalState();

// Gera um estado inicial embaralhado e garantidamente solucionável
PuzzleState generateRandomInitial(int shuffles);

// Gera um movimento aleatório válido para o estado atual
int generateRandomMove(const PuzzleState& state);

// Aplica um movimento ao estado atual (Retorna falso se bater na parede)
bool applyMove(PuzzleState& state, int move);

// Retorna movimentos possíveis para o estado atual
std::vector<int> getValidMoves(const PuzzleState& state);

#endif // PUZZLE_STATE_H
