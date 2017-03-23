//
// Created by fajqa on 22.03.17.
//

#ifndef PROJECT_NEURALNETWORK_H
#define PROJECT_NEURALNETWORK_H

#include <vector>
#include <math.h>
#include <numeric>
#include <armadillo>
#include <cstdlib>

using namespace std;
using namespace arma;

char const* greet( );

class NeuralNetwork {
private:
    vector<mat> neurons;
    vector<mat> weights;

    void initializeLayers(const vector<int> &layerSizes);

    double sigmoid(int z);

public:
    NeuralNetwork(const vector<int> &layerSizes);
    mat feedForward(mat input);
};
#endif //PROJECT_NEURALNETWORK_H
