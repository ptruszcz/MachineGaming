/*
File created by: Piotr Truszczyński
*/

#ifndef MACHINEGAMING_EVOLUTIONARYALGORITHM_H
#define MACHINEGAMING_EVOLUTIONARYALGORITHM_H

#include <vector>
#include "NeuralNetwork.h"

struct NetworkFitnessPair {
    PNeuralNetwork network;
    int fitness = 0;
};

typedef std::shared_ptr<NetworkFitnessPair> PNetworkFitnessPair;
typedef std::vector<PNetworkFitnessPair> NeuralNetworks;


class EvolutionaryAlgorithm {
private:
    static Random random;
    static bool compareNetworkFitnessPair(PNetworkFitnessPair &p1, PNetworkFitnessPair &p2); //fitness comparison

    NeuralNetworks population;
    int initial_population_size;
    double crossover_probability;
    double mutation_probability;

    int evaluateFitness(PNeuralNetwork& network);
    PNetworkFitnessPair crossover();
    void mutate(PNetworkFitnessPair& networkFitnessPair);
    PNetworkFitnessPair select();
    void removeWeakest();

public:
    EvolutionaryAlgorithm(int population_size, int input_size, int hidden_layers, int output_size,
                          double crossover_probability, double mutation_probability);
    void process(int number_of_generations, int parents_selected_per_generation);
    void processGeneration(int parents_selected_per_generation);
};

#endif //MACHINEGAMING_EVOLUTIONARYALGORITHM_H
