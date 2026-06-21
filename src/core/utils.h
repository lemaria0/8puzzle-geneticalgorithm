#ifndef UTILS_H
#define UTILS_H

#include "puzzle_state.h"

// Conta quantas peças estão fora do lugar objetivo
int countMisplacedPieces(const PuzzleState& state);

// Calcula a soma das distâncias horizontais e verticais de cada peça até seu lugar correto
int calculateManhattan(const PuzzleState& state);

// Calcula a pontuação heurística combinada do estado
int calculateHeuristics(const PuzzleState& state);

#endif // UTILS_H]
