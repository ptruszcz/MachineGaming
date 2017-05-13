#include "EvolutionaryAlgorithm.h"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

using namespace boost::python;


BOOST_PYTHON_MODULE(EvolutionaryAlgorithm_Ext) {

    class_<std::vector<double> >("vector_nn")
            .def(vector_indexing_suite<std::vector<NeuralNetwork> >());

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


    //class_<EvolutionaryAlgorithm>("EvolutionaryAlgorithm", init<EvolutionaryAlgorithmParameters>())
            //.def("breed", &EvolutionaryAlgorithm::breed)
            //.def("removeWeakestIndividuals", &EvolutionaryAlgorithm::removeWeakestIndividuals)
            //.def("getCurrentGeneration", &EvolutionaryAlgorithm::getCurrentGeneration)
            ;

}