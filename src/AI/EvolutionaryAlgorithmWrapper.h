/**
 * @class EvolutionaryAlgorithmWrapper
 * @brief Wrapper for EvolutionaryAlgorithm.
 * @details It makes EvolutionaryAlgorithm class public methods
 * fully accessible in Python.
 * @author Piotr Truszczynski
 */

#ifndef MACHINEGAMING_EVOLUTIONARYALGORITHMWRAPPER_H
#define MACHINEGAMING_EVOLUTIONARYALGORITHMWRAPPER_H

#include <boost/python.hpp>
#include "EvolutionaryAlgorithm.h"
#include "NeuralNetworkWrapper.h"

namespace py = boost::python;

class EvolutionaryAlgorithmWrapper {
private:
    EvolutionaryAlgorithm evolutionaryAlgorithm;

public:
    EvolutionaryAlgorithmWrapper();
    EvolutionaryAlgorithmWrapper(EvolutionaryAlgorithmParameters parameters);
    EvolutionaryAlgorithmWrapper(const py::object &eap);

    EvolutionaryAlgorithmParameters extractParams(const py::object &eap);

    const py::list getPopulation() const;
    const NeuralNetworkWrapper getNext();
    int getCurrentNetwork() const;
    int getCurrentGeneration() const;

    void save(py::str filename);
    void load(py::str filename);
};


#endif //MACHINEGAMING_EVOLUTIONARYALGORITHMWRAPPER_H
