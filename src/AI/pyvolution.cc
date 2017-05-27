#include "NeuralNetworkWrapper.h"
#include "EvolutionaryAlgorithm.h"

using namespace boost::python;

class EvolutionaryAlgorithmWrapper : public EvolutionaryAlgorithm {
public:
    //EvolutionaryAlgorithmWrapper(object eap) :
    //    EvolutionaryAlgorithm::EvolutionaryAlgorithm(extract<EvolutionaryAlgorithmParameters&>(eap)) {}

    EvolutionaryAlgorithmWrapper(const EvolutionaryAlgorithmParameters eap) :
            EvolutionaryAlgorithm::EvolutionaryAlgorithm(eap) {}

    static boost::shared_ptr<EvolutionaryAlgorithmWrapper> initWrapper(object const & p) {
        EvolutionaryAlgorithmParameters eap = extract<EvolutionaryAlgorithmParameters>(p);
        return boost::shared_ptr<EvolutionaryAlgorithmWrapper>(new EvolutionaryAlgorithmWrapper(eap));
    }

    const py::list getCurrentGenerationAsListOfNeuralNetworks() const {
        std::vector<PNeuralNetwork> pointers = getCurrentGeneration();
        std::vector<NeuralNetwork> population;
        for(PNeuralNetwork pn : pointers)
            population.push_back(*pn);
        return to_py_list(population);
    }

    const py::list getCurrentGenerationAsListOfSharedPtr() const {
        std::vector<PNeuralNetwork> pointers = getCurrentGeneration();
        return to_py_list(pointers);
    }
};

BOOST_PYTHON_MODULE(pyvolution) {
    register_ptr_to_python<std::shared_ptr<NeuralNetwork>>();

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

    class_<EvolutionaryAlgorithmWrapper>("EvolutionaryAlgorithm", no_init)
            .def("__init__", make_constructor(&EvolutionaryAlgorithmWrapper::initWrapper))
            .def("breed", &EvolutionaryAlgorithmWrapper::breed)
            .def("remove_weakest_individuals", &EvolutionaryAlgorithmWrapper::removeWeakestIndividuals)
            .def("get_current_generation_as_list_of_shared_ptr", &EvolutionaryAlgorithmWrapper::getCurrentGenerationAsListOfSharedPtr)
            .def("get_current_generation", &EvolutionaryAlgorithmWrapper::getCurrentGenerationAsListOfNeuralNetworks);
}