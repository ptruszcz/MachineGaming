#include <boost/test/unit_test.hpp>
#include "NeuralNetworkProxy.h"

BOOST_AUTO_TEST_SUITE(pyvolutionProxyTest)
    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    BOOST_FIXTURE_TEST_CASE(InitTest, F) {
        NeuralNetworkProxy neuralNetwork(5,5,5);
        std::vector<double> v(5, 2);
        neuralNetwork.feedForwardUsingVector(v);
        BOOST_CHECK_EQUAL(5, neuralNetwork.getOutput().n_elem);
    }

    BOOST_FIXTURE_TEST_CASE(getOutputAsVectkrTest, F) {
        NeuralNetworkProxy neuralNetwork(5,5,5);
        std::vector<double> v(5, 2);
        neuralNetwork.feedForwardUsingVector(v);
        BOOST_CHECK_EQUAL(5, neuralNetwork.getOutputAsVector().size());
        BOOST_CHECK_CLOSE(neuralNetwork.getOutput()[0], neuralNetwork.getOutputAsVector()[0], 0.00001);
        BOOST_CHECK_CLOSE(neuralNetwork.getOutput()[4], neuralNetwork.getOutputAsVector()[4], 0.00001);
    }

BOOST_AUTO_TEST_SUITE_END()

