#include <boost/test/unit_test.hpp>
#include <NeuralNetwork.h>

struct F {
    F() {
        Neuron::resetCounter();
        Connection::resetCounter();
    }
};

bool is_close(const Matrix &X, const Matrix &Y, double tol) {
    bool close = false;
    if(arma::max(arma::max(arma::abs(X-Y))) < tol)
    {
        close = true;
    }
    return close;
}

BOOST_AUTO_TEST_SUITE(NeuralNetworkTest)

    BOOST_FIXTURE_TEST_CASE(InitTest, F) {
        NeuralNetwork neuralNetwork(5,5,5);
        neuralNetwork.feedForward({1, 2, 3, 4, 5});
        BOOST_CHECK_EQUAL(5, neuralNetwork.getOutput().n_elem);
    }

    BOOST_FIXTURE_TEST_CASE(CrossoverTest, F) {
        //TODO Fix the bug. :c
        PNeuralNetwork parentA = std::make_shared<NeuralNetwork>(5,5,5);
        PNeuralNetwork parentB = std::make_shared<NeuralNetwork>(*parentA);

        PNeuralNetwork child = NeuralNetwork::crossover(parentA, parentB);

        parentA->feedForward({1, 2, 3, 4, 5});
        parentB->feedForward({1, 2, 3, 4, 5});
        child->feedForward({1, 2, 3, 4, 5});

        BOOST_CHECK_EQUAL(5, parentA->getOutput().n_elem);
        BOOST_CHECK_EQUAL(5, parentB->getOutput().n_elem);
        BOOST_CHECK_EQUAL(5, child->getOutput().n_elem);


        bool expected = is_close(parentA->getOutput(), parentB->getOutput(), 0.0);
        BOOST_ASSERT(expected);
    }

BOOST_AUTO_TEST_SUITE_END()