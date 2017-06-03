#include "NeuralNetworkWrapper.h"

NeuralNetworkWrapper::NeuralNetworkWrapper(int input_size, int hidden_layers, int output_size)
        : pNeuralNetwork(new NeuralNetwork(input_size, hidden_layers, output_size)) {}

NeuralNetworkWrapper::NeuralNetworkWrapper(PNeuralNetwork pNeuralNetwork)
        : pNeuralNetwork(pNeuralNetwork) {}

const py::list NeuralNetworkWrapper::getOutput() {
    std::vector<double> output = arma::conv_to<std::vector<double>>::from(pNeuralNetwork.get()->getOutput());
    return to_py_list(output);
}

void NeuralNetworkWrapper::feedForward(boost::python::list &input) {
    std::vector<double> input_vector = to_std_vector<double>(input);
    arma::rowvec a = arma::conv_to<arma::rowvec>::from(input_vector);
    Matrix matrix(a);
    pNeuralNetwork.get()->feedForward(matrix);
}

double NeuralNetworkWrapper::getFitness() const {
    return pNeuralNetwork.get()->getFitness();
}

void NeuralNetworkWrapper::setFitness(double fitness) {
    pNeuralNetwork.get()->setFitness(fitness);
}
