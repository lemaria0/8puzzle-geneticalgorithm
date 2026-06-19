#include "puzzle_state.h"

#include <cstdlib>
#include <algorithm>


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

PuzzleState getGoalState()
{
    PuzzleState goal{};
    int value = 1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == 2 && j == 2)
                goal.board[i][j] = 0;
            else
                goal.board[i][j] = value++;
        }
    }

    goal.emptyRow = 2;
    goal.emptyCol = 2;

    return goal;
}

std::vector<int> getValidMoves(const PuzzleState &state)
{
    std::vector<int> moves;

    if (state.emptyRow > 0)
        moves.push_back(0);

    if (state.emptyRow < 2)
        moves.push_back(1);

    if (state.emptyCol > 0)
        moves.push_back(2);

    if (state.emptyCol < 2)
        moves.push_back(3);

    return moves;
}

PuzzleState generateRandomInitial(int shuffles)
{
    PuzzleState state = getGoalState();

    for (int i = 0; i < shuffles; i++)
    {
        std::vector<int> moves = getValidMoves(state);
        int index = rand() % moves.size();
        applyMove(state, moves[index]);
    }

    return state;
}

int generateRandomMove(const PuzzleState &state)
{
    std::vector<int> validMoves = getValidMoves(state);
    int index = rand() % validMoves.size();

    return validMoves[index];
}

bool applyMove(PuzzleState &state, int move)
{
    int row = state.emptyRow;
    int col = state.emptyCol;

    switch (move)
    {
    case 0:
        row--;
        break;
    case 1:
        row++;
        break;
    case 2:
        col--;
        break;
    case 3:
        col++;
        break;
    default:
        return false;
    }

    if (row < 0 || row >= 3 || col < 0 || col >= 3)
        return false;

    std::swap(state.board[state.emptyRow][state.emptyCol], state.board[row][col]);

    state.emptyRow = row;
    state.emptyCol = col;

    return true;
}
