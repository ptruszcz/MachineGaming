#include "NeuralNetwork.h"
#include "EvolutionaryAlgorithm.h"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

using namespace boost::python;

class NeuralNetworkProxy : public NeuralNetwork {
public:
    typedef std::vector<double> vector_double;

    NeuralNetworkProxy(int input_size, int hidden_layers, int output_size) :
            NeuralNetwork::NeuralNetwork(input_size, hidden_layers, output_size) {}

    const vector_double getOutputAsVector() {
        Matrix matrix = output_;
        vector_double output;
        for (size_t i = 0; i < matrix.n_rows; ++i) {
            output[i] = arma::conv_to<double>::from(output_.row(i));
        }
        return output;
    }

    void feedForwardUsingVector(vector_double &input) {
        Matrix matrix(input);
        feedForward(matrix);
    }

    void feedForwardUsingPyList(boost::python::list &input)
    {
        vector_double v;
        for (int i = 0; i < len(input); ++i)
        {
            double d = boost::python::extract<double>(input[i]);
            v.push_back(d);
        }
    }
};


BOOST_PYTHON_MODULE(pyvolution) {
    class_<std::vector<double> >("vector_double")
            .def(vector_indexing_suite<std::vector<double> >());

    class_<NeuralNetworkProxy>("NeuralNetwork", init<int, int, int>())
            .def("feed_forward", &NeuralNetworkProxy::feedForwardUsingVector)
            .def("feed_forward_list", &NeuralNetworkProxy::feedForwardUsingPyList)
            .def("get_output", &NeuralNetworkProxy::getOutputAsVector)
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