#include "puzzle_state.h"
#include "../algorithms/genetic.h"

#include <algorithm>
#include <random>
#include <array>

static std::mt19937 &getEngine()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

bool PuzzleState::operator==(const PuzzleState &other) const
{
    return this->board == other.board;
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

std::pair<std::array<Move, 4>, size_t> getValidMovesOpt(const PuzzleState &state)
{
    std::array<Move, 4> moves{};
    size_t count = 0;

    if (state.emptyRow > 0)
        moves[count++] = Move::UP;
    if (state.emptyRow < 2)
        moves[count++] = Move::DOWN;
    if (state.emptyCol > 0)
        moves[count++] = Move::LEFT;
    if (state.emptyCol < 2)
        moves[count++] = Move::RIGHT;

    return {moves, count};
}

std::vector<int> getValidMoves(const PuzzleState &state)
{
    std::vector<int> moves;
    moves.reserve(4);

    if (state.emptyRow > 0)
        moves.push_back(Move::UP);
    if (state.emptyRow < 2)
        moves.push_back(Move::DOWN);
    if (state.emptyCol > 0)
        moves.push_back(Move::LEFT);
    if (state.emptyCol < 2)
        moves.push_back(Move::RIGHT);

    return moves;
}

PuzzleState generateRandomInitial(int shuffles)
{
    PuzzleState state = getGoalState();

    for (int i = 0; i < shuffles; i++)
    {
        int move = generateRandomMove(state);
        applyMove(state, move);
    }

    return state;
}

int generateRandomMove(const PuzzleState &state)
{
    auto [validMoves, count] = getValidMovesOpt(state);

    std::uniform_int_distribution<size_t> dist(0, count - 1);
    return static_cast<int>(validMoves[dist(getEngine())]);
}

bool applyMove(PuzzleState &state, int move)
{
    int row = state.emptyRow;
    int col = state.emptyCol;

    switch (static_cast<Move>(move))
    {
    case Move::UP:
        row--;
        break;
    case Move::DOWN:
        row++;
        break;
    case Move::LEFT:
        col--;
        break;
    case Move::RIGHT:
        col++;
        break;
    default:
        return false;
    }

    if (row < 0 || row >= 3 || col < 0 || col >= 3)
    {
        return false;
    }

    std::swap(state.board[state.emptyRow][state.emptyCol], state.board[row][col]);

    state.emptyRow = row;
    state.emptyCol = col;

    return true;
}
