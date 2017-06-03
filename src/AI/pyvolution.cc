#include "NeuralNetworkWrapper.h"
#include "EvolutionaryAlgorithmWrapper.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(pyvolution) {
    register_ptr_to_python<std::shared_ptr<NeuralNetworkWrapper>>();

    class_<NeuralNetworkWrapper>("NeuralNetwork", init<int, int, int>())
            .def("feed_forward", &NeuralNetworkWrapper::feedForward)
            .def("get_output", &NeuralNetworkWrapper::getOutput)
            .add_property("fitness", &NeuralNetworkWrapper::getFitness, &NeuralNetworkWrapper::setFitness);

    class_<EvolutionaryAlgorithmParameters>("EvolutionaryAlgorithmParameters", no_init)
            .add_property("population_size", &EvolutionaryAlgorithmParameters::population_size)
            .add_property("children_bred_per_generation",
                          &EvolutionaryAlgorithmParameters::children_bred_per_generation)
            .add_property("crossover_probability", &EvolutionaryAlgorithmParameters::crossover_probability)
            .add_property("mutation_probability", &EvolutionaryAlgorithmParameters::mutation_probability)
            .add_property("input_size", &EvolutionaryAlgorithmParameters::input_size)
            .add_property("hidden_layers", &EvolutionaryAlgorithmParameters::hidden_layers)
            .add_property("output_size", &EvolutionaryAlgorithmParameters::output_size)
            .add_property("weight_variance", &EvolutionaryAlgorithmParameters::weight_variance);

    class_<EvolutionaryAlgorithmWrapper>("EvolutionaryAlgorithm")
            .def(init<const object &>())
            .def("get_next", &EvolutionaryAlgorithmWrapper::getNext)
            .def("get_population", &EvolutionaryAlgorithmWrapper::getPopulation)
            .def("get_current_network", &EvolutionaryAlgorithmWrapper::getCurrentNetwork)
            .def("get_current_generation", &EvolutionaryAlgorithmWrapper::getCurrentGeneration)
            .def("get_population_size", &EvolutionaryAlgorithmWrapper::getPopulationSize)
            .def("get_children_bred_per_generation", &EvolutionaryAlgorithmWrapper::getChildrenBredPerGeneration)
            .def("get_crossover_probability", &EvolutionaryAlgorithmWrapper::getCrossoverProbability)
            .def("get_mutation_probability", &EvolutionaryAlgorithmWrapper::getMutationProbability)
            .def("get_hidden_layers", &EvolutionaryAlgorithmWrapper::getHiddenLayers)
            .def("get_weight_variance", &EvolutionaryAlgorithmWrapper::getWeightVariance)
            .def("save", &EvolutionaryAlgorithmWrapper::save)
            .def("load", &EvolutionaryAlgorithmWrapper::load);
    
    class_<Neuron>("Neuron", no_init)
            .def("reset_counter", &Neuron::resetCounter);

    class_<Connection>("Connection", no_init)
            .def("reset_counter", &Connection::resetCounter);
}