#include "NeuralNetworkWrapper.h"
#include "EvolutionaryAlgorithmWrapper.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(pyvolution) {
    register_ptr_to_python<std::shared_ptr<NeuralNetworkWrapper>>();

    class_<NeuralNetworkWrapper>("NeuralNetwork", init<int, int, int>())
            .def("feed_forward_vector", &NeuralNetworkWrapper::feedForwardUsingVector)
            .def("feed_forward", &NeuralNetworkWrapper::feedForwardUsingList)
            .def("get_output_vector", &NeuralNetworkWrapper::getOutputAsVector)
            .def("get_output", &NeuralNetworkWrapper::getOutputAsList)
            .add_property("fitness", &NeuralNetworkWrapper::getFitness, &NeuralNetworkWrapper::setFitness);

    class_<EvolutionaryAlgorithmParameters>("EvolutionaryAlgorithmParameters", no_init)
            .add_property("population_size", &EvolutionaryAlgorithmParameters::population_size)
            .add_property("children_bred_per_generation",
                          &EvolutionaryAlgorithmParameters::children_bred_per_generation)
            .add_property("crossover_probability", &EvolutionaryAlgorithmParameters::crossover_probability)
            .add_property("mutation_probability", &EvolutionaryAlgorithmParameters::mutation_probability)
            .add_property("randomisation_probability", &EvolutionaryAlgorithmParameters::randomisation_probability)
            .add_property("input_size", &EvolutionaryAlgorithmParameters::input_size)
            .add_property("hidden_layers", &EvolutionaryAlgorithmParameters::hidden_layers)
            .add_property("output_size", &EvolutionaryAlgorithmParameters::output_size);

    class_<EvolutionaryAlgorithmWrapper>("EvolutionaryAlgorithm")
            .def(init<const object &>())
            .def("breed", &EvolutionaryAlgorithmWrapper::breed)
            .def("remove_weakest_individuals", &EvolutionaryAlgorithmWrapper::removeWeakestIndividuals)
            .def("get_current_generation", &EvolutionaryAlgorithmWrapper::getCurrentGenerationAsListOfSharedPtr)
            .def("save", &EvolutionaryAlgorithmWrapper::save)
            .def("load", &EvolutionaryAlgorithmWrapper::load);
    
    class_<Neuron>("Neuron", no_init)
            .def("reset_counter", &Neuron::resetCounter);

    class_<Connection>("Connection", no_init)
            .def("reset_counter", &Connection::resetCounter);
}