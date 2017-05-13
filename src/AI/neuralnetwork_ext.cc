#include "NeuralNetwork.h"
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


BOOST_PYTHON_MODULE(NeuralNetwork_Ext) {
    class_<std::vector<double> >("vector_double")
            .def(vector_indexing_suite<std::vector<double> >());

    class_<NeuralNetworkProxy>("NeuralNetwork", init<int, int, int>())
            .def("feed_forward", &NeuralNetworkProxy::feedForwardUsingVector)
            .def("feed_forward_list", &NeuralNetworkProxy::feedForwardUsingPyList)
            .def("get_output", &NeuralNetworkProxy::getOutputAsVector)
            .add_property("fitness", &NeuralNetworkProxy::getFitness, &NeuralNetworkProxy::setFitness);
}