#include "puzzle_state.h"
#include "utils.h"
#include <algorithm>

// Conta o número de peças fora do lugar em relação ao estado-objetivo
int countMisplacedPieces(const PuzzleState &state)
{
    int count = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state.board[i][j] != getGoalState().board[i][j])
            {
                count++;
            }
        }
    }

    return count;
}

// Calcula a distância de Manhattan para o estado atual
int calculateManhattan(const PuzzleState &s)
{
    int distance = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int val = s.board[i][j];

            if (val != 0)
            {
                int targetRow = (val - 1) / 3;
                int targetCol = (val - 1) % 3;

                distance += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }

    return distance;
}

// Conta o número de inversões para verificar se o estado é solucionável
int countInversions(const PuzzleState &state)
{
    std::vector<int> flatBoard;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state.board[i][j] != 0)
            {
                flatBoard.push_back(state.board[i][j]);
            }
        }
    }

    int inversions = 0;
    for (int i = 0; i < flatBoard.size(); i++)
    {
        for (int j = i + 1; j < flatBoard.size(); j++)
        {
            if (flatBoard[i] > flatBoard[j])
                inversions++;
        }
    }

    return inversions;
}

// Calcula a função de fitness combinando as heurísticas
int calculateHeuristics(const PuzzleState &state)
{
    return countMisplacedPieces(state) + calculateManhattan(state);
}
