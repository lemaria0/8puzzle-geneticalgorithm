#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H

#include <vector>

struct PuzzleState {
    int board[3][3]; 
    int emptyRow;
    int emptyCol;

    bool operator==(const PuzzleState& other) const;
};

PuzzleState generateRandomInitial(int shuffles);
PuzzleState getGoalState();
std::vector<int> getValidMoves(PuzzleState state);

#endif // PUZZLE_STATE_H
