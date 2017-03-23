//
// Created by fajqa on 22.03.17.
//
#include "NeuralNetwork.h"

char const* greet( )
{
    return "Hello world";
}

NeuralNetwork::NeuralNetwork(const vector<int> &layerSizes) {
    neurons = vector<mat>(layerSizes.size());
    weights = vector<mat>(layerSizes.size() - 1);

    initializeLayers(layerSizes);
}


void NeuralNetwork::initializeLayers(const vector<int> &layerSizes) {
    int layerSize, prevLayerSize;

    neurons[0] = mat(1, layerSizes[0]);
    for (int i = 1; i < layerSizes.size(); ++i) {
        layerSize = layerSizes[i];
        prevLayerSize = layerSizes[i-1];

        neurons[i] = mat(1, layerSize);
        weights[i-1] = randu<mat>(layerSize, prevLayerSize);
    }
}

double NeuralNetwork::sigmoid(int z) {
    return 1/(1 + exp(-z));
}

mat NeuralNetwork::feedForward(mat input) {
    //TODO
    return mat();
}
