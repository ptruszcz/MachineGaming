//
// Created by fajqa on 22.03.17.
//

#ifndef PROJECT_NEURALNETWORK_H
#define PROJECT_NEURALNETWORK_H

#include <vector>
#include <armadillo>
#include <cstdlib>

char const* greet( );

class NeuralNetwork {
private:
    std::vector<arma::mat> neurons;
    std::vector<arma::mat> weights;

    void initializeLayers(const std::vector<int> &layer_sizes);
    bool compatible(const arma::mat &input);

    arma::mat sigmoid(arma::mat z);
    arma::mat sigmoidPrime(arma::mat x);

public:
    arma::mat *output;

    NeuralNetwork(const std::vector<int> &layer_sizes);
    arma::mat feedForward(arma::mat input);
    arma::mat backpropagate(arma::mat expected_output);
};
#endif //PROJECT_NEURALNETWORK_H
