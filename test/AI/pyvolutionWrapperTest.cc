#include <boost/test/unit_test.hpp>
#include "NeuralNetworkWrapper.h"

BOOST_AUTO_TEST_SUITE(pyvolutionWrapperTest)
    struct F {
        F() {
            Py_Initialize(); //necessary to avoid segfault
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    BOOST_FIXTURE_TEST_CASE(InitTest, F) {
        NeuralNetworkWrapper neuralNetwork(5,5,5);
        std::vector<double> v(5, 2);
        neuralNetwork.feedForwardUsingVector(v);
        BOOST_CHECK_EQUAL(5, neuralNetwork.getOutput().n_elem);
    }

    BOOST_FIXTURE_TEST_CASE(getOutputAsVectorTest, F) {
        NeuralNetworkWrapper neuralNetwork(5,5,5);
        std::vector<double> v(5, 2);
        neuralNetwork.feedForwardUsingVector(v);
        BOOST_CHECK_EQUAL(5, neuralNetwork.getOutputAsVector().size());
        BOOST_CHECK_CLOSE(neuralNetwork.getOutput()[0], neuralNetwork.getOutputAsVector()[0], 0.00001);
        BOOST_CHECK_CLOSE(neuralNetwork.getOutput()[4], neuralNetwork.getOutputAsVector()[4], 0.00001);
    }

    BOOST_FIXTURE_TEST_CASE(feedListTest, F) {
        NeuralNetworkWrapper neuralNetwork(5,5,5);
        py::list v;
        for(int i = 0; i < 5; i++)
            v.append(2);
        neuralNetwork.feedForwardUsingList(v);
        BOOST_CHECK_EQUAL(5, neuralNetwork.getOutput().n_elem);
    }

    BOOST_FIXTURE_TEST_CASE(getOutputAsListTest, F) {
        NeuralNetworkWrapper neuralNetwork(5,5,5);
        py::list v;
        for(int i = 0; i < 5; i++)
            v.append(2);
        neuralNetwork.feedForwardUsingList(v);
        py::list out = neuralNetwork.getOutputAsList();
        BOOST_CHECK_EQUAL(5, len(out));
    }

BOOST_AUTO_TEST_SUITE_END()

