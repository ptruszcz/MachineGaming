#include "NeuralNetworkWrapper.h"

const std::vector<double> NeuralNetworkWrapper::getOutputAsVector() {
    return arma::conv_to<std::vector<double> >::from(output_);
}

const py::list NeuralNetworkWrapper::getOutputAsList() {
    std::vector<double> output = getOutputAsVector();
    return to_py_list(output);
}

void NeuralNetworkWrapper::feedForwardUsingVector(std::vector<double> &input) {
    arma::rowvec a = arma::conv_to<arma::rowvec>::from(input);
    Matrix matrix(a);
    feedForward(matrix);
}

void NeuralNetworkWrapper::feedForwardUsingList(boost::python::list &input) {
    std::vector<double> v = to_std_vector<double>(input);
    feedForwardUsingVector(v);
}
