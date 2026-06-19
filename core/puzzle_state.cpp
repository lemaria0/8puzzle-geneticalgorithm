#include "puzzle_state.h"
#include "utils.h"
#include <cstring>
#include <cstdlib>

// Sobrescreve o operador de igualdade para comparar dois estados do tabuleiro
bool PuzzleState::operator==(const PuzzleState &other) const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != other.board[i][j])
                return false;
        }
    }
    return true;
}

// Cria o estado-objetivo (Goal State)
PuzzleState getGoalState()
{
    PuzzleState goal;
    memset(&goal, 0, sizeof(PuzzleState));

    int val = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == 2 && j == 2)
                goal.board[i][j] = 0;
            else
                goal.board[i][j] = val++;
        }
    }
    goal.emptyRow = 2;
    goal.emptyCol = 2;

    return goal;
}

// Gera um estado inicial aleatório garantidamente solucionável
PuzzleState generateRandomInitial(int shuffles)
{
    PuzzleState state = getGoalState();

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < shuffles; i++)
    {
        int dir = rand() % 4;
        int nextR = state.emptyRow + dr[dir];
        int nextC = state.emptyCol + dc[dir];

        if (nextR >= 0 && nextR < 3 && nextC >= 0 && nextC < 3)
        {
            std::swap(state.board[state.emptyRow][state.emptyCol], state.board[nextR][nextC]);
            state.emptyRow = nextR;
            state.emptyCol = nextC;
        }
    }
    return state;
}

// Obtém a lista de movimentos válidos para o estado atual do tabuleiro
std::vector<int> getValidMoves(PuzzleState state)
{
    std::vector<int> validMoves;

    if (state.emptyRow > 0)
        validMoves.push_back(0); // cima
    if (state.emptyRow < 2)
        validMoves.push_back(1); // baixo
    if (state.emptyCol > 0)
        validMoves.push_back(2); // esquerda
    if (state.emptyCol < 2)
        validMoves.push_back(3); // direita

    return validMoves;
}

// Aplica um movimento ao estado atual do tabuleiro
bool applyMove(PuzzleState &state, int move)
{
    int dr = state.emptyRow;
    int dc = state.emptyCol;

    if (move == 0)
        dr--;
    else if (move == 1)
        dr++;
    else if (move == 2)
        dc--;
    else if (move == 3)
        dc++;

    if (dr < 0 || dr >= 3 || dc < 0 || dc >= 3)
        return false;
    std::swap(state.board[state.emptyRow][state.emptyCol], state.board[dr][dc]);
    state.emptyRow = dr;
    state.emptyCol = dc;

    return true;
}
