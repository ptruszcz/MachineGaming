#include <boost/test/unit_test.hpp>
#include <NeuralNetwork.h>


BOOST_AUTO_TEST_SUITE(NeuralNetworkTest)
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

    BOOST_FIXTURE_TEST_CASE(InitTest, F) {
        NeuralNetwork neuralNetwork(5,5,5);
        neuralNetwork.feedForward({1, 2, 3, 4, 5});
        BOOST_CHECK_EQUAL(5, neuralNetwork.getOutput().n_elem);
    }

    BOOST_FIXTURE_TEST_CASE(SameParentsCrossoverTest, F) {
        PNeuralNetwork parentA = std::make_shared<NeuralNetwork>(5,5,5);
        PNeuralNetwork parentB = std::make_shared<NeuralNetwork>(*parentA);

        PNeuralNetwork child = NeuralNetwork::crossover(parentA, parentB);

        parentA->feedForward({1, 2, 3, 4, 5});
        parentB->feedForward({1, 2, 3, 4, 5});
        child->feedForward({1, 2, 3, 4, 5});

        BOOST_ASSERT(is_close(parentA->getOutput(), child->getOutput(), 0.0001));
        BOOST_ASSERT(is_close(parentB->getOutput(), child->getOutput(), 0.0001));
    }

    BOOST_FIXTURE_TEST_CASE(DifferentParentsCrossoverTest, F) {
        PNeuralNetwork parentA = std::make_shared<NeuralNetwork>(5,5,5);
        PNeuralNetwork parentB = std::make_shared<NeuralNetwork>(*parentA);
        parentB->randomizeConnections();

        PNeuralNetwork child = NeuralNetwork::crossover(parentA, parentB);

        parentA->feedForward({1, 2, 3, 4, 5});
        parentB->feedForward({1, 2, 3, 4, 5});
        child->feedForward({1, 2, 3, 4, 5});

        BOOST_ASSERT(!is_close(parentA->getOutput(), child->getOutput(), 0.0001));
        BOOST_ASSERT(!is_close(parentB->getOutput(), child->getOutput(), 0.0001));
    }

    BOOST_FIXTURE_TEST_CASE(MutationCrossoverTest, F) {
        NeuralNetwork modified(5,5,5);
        NeuralNetwork unmodified(modified);

        modified.mutate(ADD_NEURON);


        modified.feedForward({1, 2, 3, 4, 5});
        unmodified.feedForward({1, 2, 3, 4, 5});

        BOOST_ASSERT(!is_close(modified.getOutput(), unmodified.getOutput(), 0.0001));
    }

BOOST_AUTO_TEST_SUITE_END()