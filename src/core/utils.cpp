#include "utils.h"
#include "puzzle_state.h"

#include <cmath>

constexpr int MISPLACED_WEIGHT = 36;
constexpr int MANHATTAN_WEIGHT = 18;

int countMisplacedPieces(const PuzzleState &state)
{
    static const PuzzleState goal = getGoalState();
    int count = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int value = state.board[i][j];

            if (value != 0 && value != goal.board[i][j])
            {
                count++;
            }
        }
    }

    return count;
}

int calculateManhattan(const PuzzleState &state)
{
    int distance = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int value = state.board[i][j];

            if (value == 0)
            {
                continue;
            }

            int targetRow = (value - 1) / 3;
            int targetCol = (value - 1) % 3;

            distance += std::abs(i - targetRow) + std::abs(j - targetCol);
        }
    }

    return distance;
}

int calculateHeuristics(const PuzzleState &state)
{
    return (MISPLACED_WEIGHT * countMisplacedPieces(state)) + (MANHATTAN_WEIGHT * calculateManhattan(state));
}
