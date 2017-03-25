//
// Created by fajqa on 22.03.17.
//

#ifndef PROJECT_NEURALNETWORK_H
#define PROJECT_NEURALNETWORK_H

#include <vector>
#include <armadillo>
#include <cstdlib>
#include <Neuron.h>
#include "Genotype.h"

char const* greet( );

class NeuralNetwork {
private:
    Genotype genotype;

    arma::mat *output;
    std::vector<arma::mat> neurons;
    std::vector<arma::mat> weights;

    void initializeLayers(const std::vector<int> &layer_sizes);
    bool compatible(const arma::mat &input);

    arma::mat activationFunction(arma::mat z);
    arma::mat activationFunctionDerivative(arma::mat x);

public:
    NeuralNetwork(int input_size, int output_size) :
            NeuralNetwork(std::vector<int>({input_size, output_size})) {}
    NeuralNetwork(const std::vector<int> &layer_sizes);
    NeuralNetwork(const NeuralNetwork &neural_network);

    arma::mat feedForward(arma::mat input);
    arma::mat backpropagate(arma::mat expected_output);

    arma::mat getOutput();
};
#endif //PROJECT_NEURALNETWORK_H
