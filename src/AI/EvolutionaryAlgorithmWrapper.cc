#include "EvolutionaryAlgorithmWrapper.h"

EvolutionaryAlgorithmWrapper::EvolutionaryAlgorithmWrapper() {

}

EvolutionaryAlgorithmWrapper::EvolutionaryAlgorithmWrapper(EvolutionaryAlgorithmParameters parameters)
        : evolutionaryAlgorithm(parameters) {}

EvolutionaryAlgorithmWrapper::EvolutionaryAlgorithmWrapper(const py::object &eap)
        : evolutionaryAlgorithm(extractParams(eap)) {}

EvolutionaryAlgorithmParameters EvolutionaryAlgorithmWrapper::extractParams(const py::object &eap) {
    EvolutionaryAlgorithmParameters params;

    params.population_size = py::extract<int>(eap.attr("population_size"));
    params.children_bred_per_generation = py::extract<int>(eap.attr("children_bred_per_generation"));
    params.crossover_probability = py::extract<double>(eap.attr("crossover_probability"));
    params.input_size = py::extract<int>(eap.attr("input_size"));
    params.output_size = py::extract<int>(eap.attr("output_size"));
    params.mutation_probability = py::extract<double>(eap.attr("mutation_probability"));
    params.hidden_layers = py::extract<int>(eap.attr("hidden_layers"));
    params.weight_variance = py::extract<double>(eap.attr("weight_variance"));

    return params;
}

const py::list EvolutionaryAlgorithmWrapper::getCurrentGeneration() const {
    std::vector<PNeuralNetwork> pnn = evolutionaryAlgorithm.getCurrentGeneration();
    std::vector<std::shared_ptr<NeuralNetworkWrapper>> pwnn;
    for(auto &p : pnn) {
        pwnn.push_back(std::make_shared<NeuralNetworkWrapper>(p));
    }
    return to_py_list(pwnn);
}

const NeuralNetworkWrapper EvolutionaryAlgorithmWrapper::getNext() {
    return NeuralNetworkWrapper(evolutionaryAlgorithm.getNext());
}

void EvolutionaryAlgorithmWrapper::save(py::str filename) {
    evolutionaryAlgorithm.save(boost::python::extract<std::string>(filename));
}

void EvolutionaryAlgorithmWrapper::load(py::str filename) {
    evolutionaryAlgorithm.load(boost::python::extract<std::string>(filename));
}
