#include "../core/puzzle_state.h"
#include <vector>

struct Individual {
    std::vector<int> genes;

    PuzzleState bestState;
    int bestFitness;

    int stepsToBest;
};

bool applyMove(PuzzleState& state, int move);
void applyGenes(Individual& ind, const PuzzleState& initialState);
std::vector<Individual> generateInitialPopulation(int populationSize, int geneLength, int shuffleMoves);