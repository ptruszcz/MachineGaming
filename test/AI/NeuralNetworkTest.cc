#define BOOST_TEST_MODULE "NeuralNetworkTest"
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

    static void serialize(PNeuralNetwork &neural_network,
                          std::string filename) {
        std::ofstream ofs(filename);
        boost::archive::text_oarchive oa(ofs);
        oa << *neural_network;
    }

    static PNeuralNetwork deserialize(std::string filename) {
        PNeuralNetwork neural_network = std::make_unique<NeuralNetwork>();
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia >> *neural_network;
        return std::move(neural_network);
    }

    BOOST_FIXTURE_TEST_CASE(InitTest, F) {
        NeuralNetwork neuralNetwork(5,5,5);
        neuralNetwork.feedForward({1, 2, 3, 4, 5});
        BOOST_CHECK_EQUAL(5, neuralNetwork.getOutput().n_elem);
    }

    BOOST_FIXTURE_TEST_CASE(SameParentsCrossoverTest, F) {
        PNeuralNetwork parentA = std::make_unique<NeuralNetwork>(5,5,5);
        PNeuralNetwork parentB = std::make_unique<NeuralNetwork>(*parentA);

        PNeuralNetwork child = NeuralNetwork::crossover(*parentA, *parentB);

        parentA->feedForward({1, 2, 3, 4, 5});
        parentB->feedForward({1, 2, 3, 4, 5});
        child->feedForward({1, 2, 3, 4, 5});

        BOOST_ASSERT(is_close(parentA->getOutput(), child->getOutput(), 0.0001));
        BOOST_ASSERT(is_close(parentB->getOutput(), child->getOutput(), 0.0001));
    }

    BOOST_FIXTURE_TEST_CASE(DifferentParentsCrossoverTest, F) {
        PNeuralNetwork parentA = std::make_unique<NeuralNetwork>(5,5,5);
        PNeuralNetwork parentB = std::make_unique<NeuralNetwork>(*parentA);
        parentB->randomizeAllWeights();

        PNeuralNetwork child = NeuralNetwork::crossover(*parentA, *parentB);

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

    BOOST_FIXTURE_TEST_CASE(SerializationTest, F) {
        Matrix input = {1, 1, 1, 1, 1};

        PNeuralNetwork serialized_neural_network = std::make_unique<NeuralNetwork>(5, 5, 5);
        serialized_neural_network->feedForward(input);
        Matrix expected = serialized_neural_network->getOutput();
        serialize(serialized_neural_network, "NeuralNetworkTest.mg");

        PNeuralNetwork deserialized_neural_network = deserialize("NeuralNetworkTest.mg");
        deserialized_neural_network->feedForward(input);
        Matrix actual = deserialized_neural_network->getOutput();

        BOOST_ASSERT(is_close(expected, actual, 0.001));
    }

BOOST_AUTO_TEST_SUITE_END()