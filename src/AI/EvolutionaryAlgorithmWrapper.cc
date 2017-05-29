#include "EvolutionaryAlgorithmWrapper.h"

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
    params.randomisation_probability = py::extract<double>(eap.attr("randomisation_probability"));

    return params;
}

const py::list EvolutionaryAlgorithmWrapper::getCurrentGenerationAsListOfSharedPtr() const {
    std::vector<PNeuralNetwork> pnn = evolutionaryAlgorithm.getCurrentGeneration();
    std::vector<std::shared_ptr<NeuralNetworkWrapper>> pwnn;
    for(auto& p : pnn) {
        pwnn.push_back(std::make_shared<NeuralNetworkWrapper>(p));
    }
    return to_py_list(pwnn);
}

const NeuralNetworks &EvolutionaryAlgorithmWrapper::getCurrentGeneration() const {
    return evolutionaryAlgorithm.getCurrentGeneration();
}

void EvolutionaryAlgorithmWrapper::breed() {
    evolutionaryAlgorithm.breed();
}

void EvolutionaryAlgorithmWrapper::removeWeakestIndividuals() {
    evolutionaryAlgorithm.removeWeakestIndividuals();
}
