#include "NeuralNetworkProxy.h"
#include "EvolutionaryAlgorithm.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(pyvolution) {
    class_<std::vector<double> >("vector_double")
            .def(vector_indexing_suite<std::vector<double> >());

    class_<NeuralNetworkProxy>("NeuralNetwork", init<int, int, int>())
            .def("feed_forward_vector", &NeuralNetworkProxy::feedForwardUsingVector)
            .def("feed_forward", &NeuralNetworkProxy::feedForwardUsingPyList)
            .def("get_output_vector", &NeuralNetworkProxy::getOutputAsVector)
            .def("get_output", &NeuralNetworkProxy::getOutputAsList)
            .add_property("fitness", &NeuralNetworkProxy::getFitness, &NeuralNetworkProxy::setFitness);

    class_<std::vector<PNeuralNetwork> >("vector_nn")
            .def(vector_indexing_suite<std::vector<PNeuralNetwork> >());

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


    class_<EvolutionaryAlgorithm>("EvolutionaryAlgorithm", init<EvolutionaryAlgorithmParameters>())
            .def("breed", &EvolutionaryAlgorithm::breed)
            .def("removeWeakestIndividuals", &EvolutionaryAlgorithm::removeWeakestIndividuals)
            //.def("getCurrentGeneration", &EvolutionaryAlgorithm::getCurrentGeneration)
            ;
}