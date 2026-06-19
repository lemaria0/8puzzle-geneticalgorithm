#include "../core/puzzle_state.h"
#include "../core/utils.h"
#include <vector>

// Estrutura do indivíduo
struct Individual
{
    std::vector<int> genes;

    PuzzleState bestState;
    int stepsToBest;

    double bestFitness;
};

bool applyMove(PuzzleState &state, int move);
void applyGenes(Individual &ind, const PuzzleState &initialState);
std::vector<Individual> generateInitialPopulation(int populationSize, int geneLength, int shuffleMoves);
