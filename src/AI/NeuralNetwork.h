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

    void initializeLayers(const std::vector<int> &layerSizes);
    bool compatible(const arma::mat &input);

    arma::mat sigmoid(arma::mat z);

public:
    NeuralNetwork(const std::vector<int> &layerSizes);
    arma::mat feedForward(arma::mat input);
};
#endif //PROJECT_NEURALNETWORK_H
