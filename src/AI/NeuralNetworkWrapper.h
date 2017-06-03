#ifndef MACHINEGAMING_NEURALNETWORKPROXY_H
#define MACHINEGAMING_NEURALNETWORKPROXY_H

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "NeuralNetwork.h"

namespace py = boost::python;

template<typename T>
std::vector< T > to_std_vector(const py::list& iterable) {
    return std::vector<T>(py::stl_input_iterator<T>(iterable), py::stl_input_iterator<T>());
}

template<typename T>
py::list to_py_list(const std::vector<T>& vector) {
    py::list list;
    for(const auto& e : vector)
        list.append(e);
    return list;
}


class NeuralNetworkWrapper {
private:
    std::shared_ptr<NeuralNetwork> pNeuralNetwork;

public:
    NeuralNetworkWrapper(int input_size, int hidden_layers, int output_size);
    NeuralNetworkWrapper(PNeuralNetwork pNeuralNetwork);

    const py::list getOutput();
    void feedForward(py::list &input);
    double getFitness() const;
    void setFitness(double fitness);
};


#endif //MACHINEGAMING_NEURALNETWORKPROXY_H
