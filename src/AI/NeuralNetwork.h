/*
File created by: Jakub Fajkowski
*/

#ifndef PROJECT_NEURALNETWORK_H
#define PROJECT_NEURALNETWORK_H

#include <vector>
#include <armadillo>
#include <cstdlib>
#include "Genome.h"
#include "Phenome.h"

const std::string greet( );

class NeuralNetwork;
typedef std::shared_ptr<NeuralNetwork> PNeuralNetwork;
typedef std::vector<PNeuralNetwork> NeuralNetworks;

class NeuralNetwork {
private:
    Genome genome_;
    Phenome phenome_;
    double fitness_ = 0;

    bool compatible(const Matrix &input);

    Matrix activationFunction(Matrix z);

public:
    NeuralNetwork(int input_size, int hidden_layers, int output_size);
    NeuralNetwork(const NeuralNetwork &neural_network);
    NeuralNetwork(const Genome &genome);

    static PNeuralNetwork crossover(PNeuralNetwork &parent_a, PNeuralNetwork &parent_b);
    void mutate(const MutationType &mutation_type);

    void randomizeAllWeights();
    Matrix feedForward(Matrix input);

    Matrix &getOutput();
    double getFitness() const;
    void setFitness(double fitness);

    bool operator==(const NeuralNetwork &rhs) const;
    bool operator!=(const NeuralNetwork &rhs) const;
};
#endif //PROJECT_NEURALNETWORK_H
