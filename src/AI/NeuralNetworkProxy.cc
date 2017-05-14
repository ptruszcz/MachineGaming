#include "NeuralNetworkProxy.h"

const std::vector<double> NeuralNetworkProxy::getOutputAsVector() {
    return arma::conv_to<std::vector<double> >::from(output_);
}

const py::list NeuralNetworkProxy::getOutputAsList() {
    std::vector<double> output = getOutputAsVector();
    py::object get_iter = py::iterator<std::vector<double> >();
    py::object iter = get_iter(output);
    py::list l(iter);
    return l;
}

void NeuralNetworkProxy::feedForwardUsingVector(std::vector<double> &input) {
    arma::rowvec a = arma::conv_to<arma::rowvec>::from(input);
    Matrix matrix(a);
    feedForward(matrix);
}

void NeuralNetworkProxy::feedForwardUsingPyList(boost::python::list &input) {
    std::vector<double> v = to_std_vector<double>(input);
    // TODO: if to_std_vector won't work in python use code below
    /*for (int i = 0; i < len(input); ++i) {
        double d = py::extract<double>(input[i]);
        v.push_back(d);
    }*/
    feedForwardUsingVector(v);
}