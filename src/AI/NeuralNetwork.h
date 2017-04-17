#ifndef PROJECT_NEURALNETWORK_H
#define PROJECT_NEURALNETWORK_H

#include <vector>
#include <armadillo>
#include <cstdlib>
#include <Neuron.h>
#include "Genome.h"

char const* greet( );

class NeuralNetwork {
private:
    Genome genome;
    // TODO Phenome instead of neurons and weights.

    arma::mat *output;
    std::vector<arma::mat> neurons;
    std::vector<arma::mat> weights;

    void initializeLayers(const std::vector<int> &layer_sizes);
    bool compatible(const arma::mat &input);

    arma::mat activationFunction(arma::mat z);
    arma::mat activationFunctionDerivative(arma::mat x);

public:
    NeuralNetwork(int input_size, int output_size) :
            NeuralNetwork(std::vector<int>({input_size, output_size})), genome(0, 0, 0) {}
    NeuralNetwork(const std::vector<int> &layer_sizes);
    NeuralNetwork(const NeuralNetwork &neural_network);

    arma::mat feedForward(arma::mat input);
    arma::mat backpropagate(arma::mat expected_output);

    arma::mat getOutput();
};
#endif //PROJECT_NEURALNETWORK_H
