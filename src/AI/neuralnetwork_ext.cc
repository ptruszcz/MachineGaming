#include "NeuralNetwork.h"
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(NeuralNetwork_Ext) {
        using namespace boost::python;
        def("greet", greet);
}