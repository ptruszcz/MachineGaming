#ifndef MACHINEGAMING_NEURALNETWORKPROXY_H
#define MACHINEGAMING_NEURALNETWORKPROXY_H

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "NeuralNetwork.h"

namespace py = boost::python;

template<typename T>
inline std::vector< T > to_std_vector(const py::list& iterable) {
    return std::vector<T>(py::stl_input_iterator<T>(iterable), py::stl_input_iterator<T>());
}

class NeuralNetworkProxy : public NeuralNetwork {
public:
    NeuralNetworkProxy(int input_size, int hidden_layers, int output_size) :
            NeuralNetwork::NeuralNetwork(input_size, hidden_layers, output_size) {}

    const std::vector<double> getOutputAsVector();
    const py::list getOutputAsList();
    void feedForwardUsingVector(std::vector<double> &input);
    void feedForwardUsingPyList(py::list &input);
};


#endif //MACHINEGAMING_NEURALNETWORKPROXY_H
