#include <GLFW/glfw3.h>
#include <iostream>

#include "core/puzzle_state.h"
#include "core/utils.h"
#include "algorithms/genetic.h"

#include "render/renderer.h"

int indexInitial = 0;
int indexFinal = 0;

void printBoard(const PuzzleState &state)
{
    std::cout << "+---+---+---+\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            if (state.board[i][j] == 0)
                std::cout << "  | ";
            else
                std::cout << state.board[i][j] << " | ";
        }
        std::cout << "\n+---+---+---+\n";
    }
}

std::vector<PuzzleState> reconstructPath(
    const PuzzleState &initialState,
    const Individual &individual)
{
    std::vector<PuzzleState> path;

    PuzzleState currentState = initialState;
    path.push_back(currentState);

    for (int i = 0; i < individual.stepsToBest; i++)
    {
        if (applyMove(
                currentState,
                static_cast<int>(individual.genes[i])))
        {
            path.push_back(currentState);
        }
    }

    return path;
}

void processInputInitial(GLFWwindow *window, int maxSize)
{
    static bool leftPressed = false;
    static bool rightPressed = false;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (!rightPressed && indexInitial < maxSize - 1)
            indexInitial++;

        rightPressed = true;
    }
    else
        rightPressed = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (!leftPressed && indexInitial > 0)
            indexInitial--;

        leftPressed = true;
    }
    else
        leftPressed = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void processInputFinal(GLFWwindow *window, int maxSize)
{
    static bool leftPressed = false;
    static bool rightPressed = false;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (!rightPressed && indexFinal < maxSize - 1)
            indexFinal++;

        rightPressed = true;
    }
    else
        rightPressed = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (!leftPressed && indexFinal > 0)
            indexFinal--;

        leftPressed = true;
    }
    else
        leftPressed = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    std::cout << "Gerando tabuleiro inicial...\n";
    PuzzleState initialState = generateRandomInitial(30);

    std::cout << "\n--- TABULEIRO INICIAL GENERADO ---\n";
    printBoard(initialState);

    int populationSize = 100;
    int geneLength = 50;
    int maxGenerations = 1000;
    double elitismRate = 0.10;
    double crossoverRate = 0.30;
    double mutationRate = 0.02;

    std::cout << "\nExecutando o Algoritmo Genetico...\n";
    GeneticResult result = runGeneticAlgorithm(
        initialState, populationSize, geneLength, maxGenerations,
        elitismRate, crossoverRate, mutationRate);

    auto initialPath = reconstructPath(initialState, result.bestInitial);
    auto finalPath = reconstructPath(initialState, result.bestFinal);

    std::cout << "\n=========================================\n";
    std::cout << "         RELATORIO DE EXECUCAO           \n";
    std::cout << "=========================================\n";
    std::cout << "Geracoes computadas : " << result.totalGenerations << "\n";
    std::cout << "Fitness inicial     : " << result.bestInitial.bestFitness << "\n";
    std::cout << "Fitness final       : " << result.bestFinal.bestFitness << "\n";
    std::cout << "Status do objetivo  : " << (result.solved ? "Sucesso" : "Falha") << "\n";
    std::cout << "Passos ate a meta   : " << result.bestFinal.stepsToBest << "\n";
    std::cout << "Estagnacoes         : " << result.bestFinal.stagnation << "\n";
    std::cout << "=========================================\n";

    std::cout << "\n--- MELHOR ESTADO ALCANCADO PELO INDIVIDUO FINAL ---\n";
    printBoard(result.bestFinal.bestState);

    std::cout << "Distancia Heuristica ate o Objetivo: " << calculateHeuristics(result.bestFinal.bestState) << "\n";
    std::cout << "=========================================\n";

    if (!glfwInit())
    {
        std::cout << "Erro GLFW\n";
        return -1;
    }

    GLFWwindow *windowInitial =
        glfwCreateWindow(500, 500, "MELHOR DA PRIMEIRA GERACAO", NULL, NULL);

    GLFWwindow *windowFinal =
        glfwCreateWindow(500, 500, "MELHOR FINAL", NULL, windowInitial);

    if (!windowInitial || !windowFinal)
    {
        std::cout << "Erro ao criar janelas\n";
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(windowInitial) &&
           !glfwWindowShouldClose(windowFinal))
    {
        glfwPollEvents();

        // Primeira geração
        glfwMakeContextCurrent(windowInitial);

        glClear(GL_COLOR_BUFFER_BIT);
        processInputInitial(windowInitial, initialPath.size());
        renderState(initialPath[indexInitial]);
        glfwSwapBuffers(windowInitial);

        // Melhor final
        glfwMakeContextCurrent(windowFinal);

        glClear(GL_COLOR_BUFFER_BIT);
        processInputFinal(windowFinal, finalPath.size());
        renderState(finalPath[indexFinal]);
        glfwSwapBuffers(windowFinal);
    }

    glfwDestroyWindow(windowInitial);
    glfwDestroyWindow(windowFinal);
    glfwTerminate();

    return 0;
}
