#include "NeuralNetwork.h"

const std::string greet( )
{
    return std::string("Hello world");
}
/*

NeuralNetwork::NeuralNetwork(const std::vector<int> &layer_sizes) : genome(0, 0, 0) {
    neurons = std::vector<arma::mat>(layer_sizes.size());
    output = &neurons.back();

    weights = std::vector<arma::mat>(layer_sizes.size() - 1);

    initializeLayers(layer_sizes);
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork &neural_network) : genome(0, 0, 0) {
    neurons = std::vector<arma::mat>(neural_network.neurons);
    output = &neurons.back();

    weights = std::vector<arma::mat>(neural_network.weights);
}

void NeuralNetwork::initializeLayers(const std::vector<int> &layer_sizes) {
    int layer_size, prev_layer_size;

    neurons[0] = arma::mat(1, layer_sizes[0]);
    for (int i = 1; i < layer_sizes.size(); ++i) {
        layer_size = layer_sizes[i];
        prev_layer_size = layer_sizes[i-1];

        neurons[i] = arma::mat(1, layer_size);
        weights[i-1] = arma::randu<arma::mat>(prev_layer_size, layer_size) * 10 - 5;
    }
}

arma::mat NeuralNetwork::activationFunction(arma::mat z) {
    return 1/(1 + arma::exp(-z));
}

arma::mat NeuralNetwork::activationFunctionDerivative(arma::mat z) {
    return z % (1 - z);
}

arma::mat NeuralNetwork::feedForward(arma::mat input) {
    if (!compatible(input)) return arma::mat();

    neurons[0] = input;
    for (int i = 0; i < weights.size(); ++i) {
        neurons[i + 1] = activationFunction(neurons[i] * weights[i]);
    }
    return *output;
}

bool NeuralNetwork::compatible(const arma::mat &input) {
    return size(neurons[0]) == size(input);
}

arma::mat NeuralNetwork::backpropagate(arma::mat expected_output) {
    arma::mat output_error = expected_output - *output;

    arma::mat layer_error = output_error;
    arma::mat layer_delta;

    for (int i = (int) (weights.size() - 1); i >= 0; --i) {
        layer_delta = layer_error % activationFunctionDerivative(neurons[i + 1]);
        layer_error = layer_delta * weights[i].t();
        weights[i] += neurons[i].t() * layer_delta;
    }

    return arma::abs(output_error);
}

arma::mat NeuralNetwork::getOutput() {
    return *output;
}
*/
