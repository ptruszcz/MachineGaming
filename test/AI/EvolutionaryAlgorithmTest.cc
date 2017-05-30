#define BOOST_TEST_MODULE "EvolutionaryAlgorithmTest"
#include <boost/test/unit_test.hpp>
#include "EvolutionaryAlgorithm.h"

BOOST_AUTO_TEST_SUITE(EvolutionaryAlgorithmTest)
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

    BOOST_FIXTURE_TEST_CASE(GenerationSizeTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 2;
        p.crossover_probability = 1;
        p.mutation_probability = 0.5;
        p.randomisation_probability = 0.1;
        p.input_size = 2;
        p.hidden_layers = 2;
        p.output_size = 1;

        EvolutionaryAlgorithm evolutionaryAlgorithm(p);
        BOOST_CHECK_EQUAL(p.population_size, evolutionaryAlgorithm.getCurrentGeneration().size());

        evolutionaryAlgorithm.breed();
        BOOST_CHECK_EQUAL(p.population_size + p.children_bred_per_generation,
                          evolutionaryAlgorithm.getCurrentGeneration().size());

        evolutionaryAlgorithm.removeWeakestIndividuals();
        BOOST_CHECK_EQUAL(p.population_size, evolutionaryAlgorithm.getCurrentGeneration().size());
    }

    BOOST_FIXTURE_TEST_CASE(PreferFitterNetworksTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 8;
        p.crossover_probability = 1;
        p.mutation_probability = 0.5;
        p.randomisation_probability = 0.1;
        p.input_size = 2;
        p.hidden_layers = 2;
        p.output_size = 1;

        EvolutionaryAlgorithm evolutionaryAlgorithm(p);
        evolutionaryAlgorithm.breed();

        int i = 0;
        for (auto& individual: evolutionaryAlgorithm.getCurrentGeneration()) {
            individual->setFitness(++i);
        }

        evolutionaryAlgorithm.removeWeakestIndividuals();

        bool contains_nine = false;
        bool contains_ten = false;
        for (auto& individual: evolutionaryAlgorithm.getCurrentGeneration()) {
            contains_nine = contains_nine || individual->getFitness() == 9;
            contains_ten = contains_ten || individual->getFitness() == 10;
        }

        BOOST_ASSERT(contains_nine);
        BOOST_ASSERT(contains_ten);
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
        p.weight_variance = 50.0;

        EvolutionaryAlgorithm evolutionaryAlgorithm(p);
        trainXOR(evolutionaryAlgorithm.getCurrentGeneration());

        int i = 0;
        while (evolutionaryAlgorithm.getCurrentGeneration()[0]->getFitness() < 3.99) {
            evolutionaryAlgorithm.breed();
            trainXOR(evolutionaryAlgorithm.getCurrentGeneration());
            evolutionaryAlgorithm.removeWeakestIndividuals();

            if (++i % 50 == 0) {
                std::cout << "\rBest fit: " << evolutionaryAlgorithm.getCurrentGeneration()[0]->getFitness() << std::flush;
            }
        }

        std::cout << "\rBest fit: " << evolutionaryAlgorithm.getCurrentGeneration()[0]->getFitness() << std::flush;
    }

    BOOST_FIXTURE_TEST_CASE(SerializationTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 5;
        p.crossover_probability = 1;
        p.mutation_probability = 0.5;
        p.randomisation_probability = 0.1;
        p.input_size = 5;
        p.hidden_layers = 5;
        p.output_size = 5;
        p.weight_variance = 50.0;

        EvolutionaryAlgorithm serialized_ea(p);

        serialized_ea.save("EvolutionaryAlgorithmTest.mg");

        EvolutionaryAlgorithm deserialized_ea;
        deserialized_ea.load("EvolutionaryAlgorithmTest.mg");

        NeuralNetworks serialized_nn = serialized_ea.getCurrentGeneration();
        NeuralNetworks deserialized_nn = deserialized_ea.getCurrentGeneration();

        Matrix input = {1, 1, 1, 1, 1};
        for (int i = 0; i < p.population_size; ++i) {
            serialized_nn[i]->feedForward(input);
            deserialized_nn[i]->feedForward(input);

            Matrix expected = serialized_nn[i]->getOutput();
            Matrix actual = deserialized_nn[i]->getOutput();

            BOOST_ASSERT(is_close(expected, actual, 0.0001));
        }

    }

BOOST_AUTO_TEST_SUITE_END()
