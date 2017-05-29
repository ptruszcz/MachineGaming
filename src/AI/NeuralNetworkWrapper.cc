#include "NeuralNetworkWrapper.h"

NeuralNetworkWrapper::NeuralNetworkWrapper(int input_size, int hidden_layers, int output_size)
        : pNeuralNetwork(new NeuralNetwork(input_size, hidden_layers, output_size)) {}

NeuralNetworkWrapper::NeuralNetworkWrapper(PNeuralNetwork pNeuralNetwork)
        : pNeuralNetwork(pNeuralNetwork) {}

const std::vector<double> NeuralNetworkWrapper::getOutputAsVector() {
    return arma::conv_to<std::vector<double> >::from(pNeuralNetwork.get()->getOutput());
}

const py::list NeuralNetworkWrapper::getOutputAsList() {
    std::vector<double> output = getOutputAsVector();
    return to_py_list(output);
}

void NeuralNetworkWrapper::feedForwardUsingVector(std::vector<double> &input) {
    arma::rowvec a = arma::conv_to<arma::rowvec>::from(input);
    Matrix matrix(a);
    pNeuralNetwork.get()->feedForward(matrix);
}

void NeuralNetworkWrapper::feedForwardUsingList(boost::python::list &input) {
    std::vector<double> v = to_std_vector<double>(input);
    feedForwardUsingVector(v);
}

const Matrix& NeuralNetworkWrapper::getOutput() const {
    return pNeuralNetwork.get()->getOutput();
}

double NeuralNetworkWrapper::getFitness() const {
    return pNeuralNetwork.get()->getFitness();
}

void NeuralNetworkWrapper::setFitness(double fitness) {
    pNeuralNetwork.get()->setFitness(fitness);
}
