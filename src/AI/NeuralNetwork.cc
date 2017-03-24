//
// Created by fajqa on 22.03.17.
//
#include "NeuralNetwork.h"

char const* greet( )
{
    return "Hello world";
}

NeuralNetwork::NeuralNetwork(const std::vector<int> &layerSizes) {
    neurons = std::vector<arma::mat>(layerSizes.size());
    weights = std::vector<arma::mat>(layerSizes.size() - 1);

    initializeLayers(layerSizes);
}


void NeuralNetwork::initializeLayers(const std::vector<int> &layerSizes) {
    int layerSize, prevLayerSize;

    neurons[0] = arma::mat(1, layerSizes[0]);
    for (int i = 1; i < layerSizes.size(); ++i) {
        layerSize = layerSizes[i];
        prevLayerSize = layerSizes[i-1];

        neurons[i] = arma::mat(1, layerSize);
        weights[i-1] = arma::randu<arma::mat>(prevLayerSize, layerSize) * 10 - 5;
    }
}

arma::mat NeuralNetwork::sigmoid(arma::mat z) {
    return 1/(1 + arma::exp(-z));
}

arma::mat NeuralNetwork::feedForward(arma::mat input) {
    if (!compatible(input)) return arma::mat();

    neurons[0] = input;
    for (int i = 0; i < weights.size(); ++i) {
        neurons[i + 1] = sigmoid(neurons[i] * weights[i]);
    }
    return neurons.back();
}

bool NeuralNetwork::compatible(const arma::mat &input) {
    return size(neurons[0]) == size(input);
}
