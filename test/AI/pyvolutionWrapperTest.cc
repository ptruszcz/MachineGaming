#include <boost/test/unit_test.hpp>
#include "NeuralNetworkWrapper.h"
#include "EvolutionaryAlgorithmWrapper.h"

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

    void trainXOR(const NeuralNetworks &networks) {
        double fitness;
        for (auto& network: networks) {
            if (network->getFitness() == 0) {
                fitness = 0;

                network->feedForward({0, 0});
                fitness += 1 - std::abs(network->getOutput()(0));
                //std::cout << "0 XOR 0 ~ " << network->getOutput()(0) << std::endl;

                network->feedForward({0, 1});
                fitness += network->getOutput()(0);
                //std::cout << "0 XOR 1 ~ " << network->getOutput()(0) << std::endl;

                network->feedForward({1, 0});
                fitness += network->getOutput()(0);
                //std::cout << "1 XOR 0 ~ " << network->getOutput()(0) << std::endl;

                network->feedForward({1, 1});
                fitness += 1 - std::abs(network->getOutput()(0));
                //std::cout << "1 XOR 1 ~ " << network->getOutput()(0) << std::endl;

                //std::cout << "Fitness: " << fitness << std::endl;
                //std::cout << "---------------------" << std::endl;

                network->setFitness(fitness);
            }
        }
    }

    BOOST_FIXTURE_TEST_CASE(ImproveResultsTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 5;
        p.crossover_probability = 1;
        p.mutation_probability = 0.5;
        p.randomisation_probability = 0.1;
        p.input_size = 2;
        p.hidden_layers = 2;
        p.output_size = 1;

        EvolutionaryAlgorithmWrapper evolutionaryAlgorithm(p);
        trainXOR(evolutionaryAlgorithm.getCurrentGeneration());

        while (evolutionaryAlgorithm.getCurrentGeneration()[0]->getFitness() < 3.50) {
            evolutionaryAlgorithm.breed();
            trainXOR(evolutionaryAlgorithm.getCurrentGeneration());
            evolutionaryAlgorithm.removeWeakestIndividuals();

            std::cout << "Wrapper Best fit: " << evolutionaryAlgorithm.getCurrentGeneration()[0]->getFitness() << std::endl;
        }
    }

BOOST_AUTO_TEST_SUITE_END()

