#define BOOST_TEST_MODULE "WrappersTest"
#include <boost/test/unit_test.hpp>
#include "NeuralNetworkWrapper.h"
#include "EvolutionaryAlgorithmWrapper.h"

BOOST_AUTO_TEST_SUITE(WrappersTest)
    struct F {
        F() {
            Py_Initialize(); //necessary to avoid segfault
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    BOOST_FIXTURE_TEST_CASE(feedListTest, F) {
        NeuralNetworkWrapper neuralNetwork(5,5,5);
        py::list v;
        for(int i = 0; i < 5; i++)
            v.append(2);
        neuralNetwork.feedForward(v);
        BOOST_CHECK_EQUAL(5, boost::python::len(neuralNetwork.getOutput()));
    }

    BOOST_FIXTURE_TEST_CASE(getOutputAsListTest, F) {
        NeuralNetworkWrapper neuralNetwork(5,5,5);
        py::list v;
        for(int i = 0; i < 5; i++)
            v.append(2);
        neuralNetwork.feedForward(v);
        py::list out = neuralNetwork.getOutput();
        BOOST_CHECK_EQUAL(5, len(out));
    }

BOOST_AUTO_TEST_SUITE_END()

