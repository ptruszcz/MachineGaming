/*
File created by: Piotr Truszczyński
*/

#ifndef MACHINEGAMING_EVOLUTIONARYALGORITHM_H
#define MACHINEGAMING_EVOLUTIONARYALGORITHM_H

#include <vector>
#include "NeuralNetwork.h"

struct EvolutionaryAlgorithmParameters {
    int population_size = 10;
    int children_bred_per_generation = 2;
    double crossover_probability = 0.5;
    double mutation_probability = 0.5;
    double randomisation_probability = 0.1;
    int input_size = 1;
    int hidden_layers = 1;
    int output_size = 1;

};

class EvolutionaryAlgorithm {
private:
    static Random random;
    static bool compareNeuralNetworks(const PNeuralNetwork &p1, const PNeuralNetwork &p2); //fitness_ comparison

    NeuralNetworks population_;
    int population_size_;
    int children_bred_per_generation_;
    double crossover_probability_;
    double mutation_probability_;
    double randomisation_probability_;

    void generateInitialPopulation(int input_size, int hidden_layers, int output_size);
    NeuralNetwork* select();
    PNeuralNetwork crossover();
    void mutate(NeuralNetwork& neural_network);

public:
    EvolutionaryAlgorithm(EvolutionaryAlgorithmParameters p);
    EvolutionaryAlgorithm(const EvolutionaryAlgorithm &eA);

    void breed();
    void removeWeakestIndividuals();

    const NeuralNetworks &getCurrentGeneration() const;
};

#endif //MACHINEGAMING_EVOLUTIONARYALGORITHM_H
