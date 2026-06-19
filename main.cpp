#include <iostream>
#include <vector>

#include "core/puzzle_state.h"
#include "algorithms/genetic.h"
#include "render/renderer.h"


int main()
{
    std::vector<Individual> population = generateInitialPopulation(10, 10, 250);

    std::cout << "Populacao inicial\n";

    for (const Individual& ind : population)
    {
        std::cout
            << "Fitness: "
            << ind.bestFitness
            << " | Passos: "
            << ind.stepsToBest
            << " | Resolvido: "
            << ind.solved
            << "\n";
    }

    std::cout << "\n------\n";

    orderPopulation(population);

    std::cout << "Populacao ordenada\n";

    for (const Individual& ind : population)
    {
        std::cout
            << "Fitness: "
            << ind.bestFitness
            << " | Passos: "
            << ind.stepsToBest
            << " | Resolvido: "
            << ind.solved
            << "\n";
    }

    return 0;
}
