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

    void trainXOR(const PNeuralNetwork &network) {
        double fitness;
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

    BOOST_FIXTURE_TEST_CASE(GenerationSizeTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 2;
        p.crossover_probability = 1;
        p.mutation_probability = 0.5;
        p.input_size = 2;
        p.hidden_layers = 2;
        p.output_size = 1;
        p.weight_variance = 10;

        EvolutionaryAlgorithm evolutionaryAlgorithm(p);
        BOOST_CHECK_EQUAL(p.population_size, evolutionaryAlgorithm.getPopulation().size());


        for (int i = 0; i < p.population_size; ++i) {
            evolutionaryAlgorithm.getNext();
            BOOST_CHECK_EQUAL(p.population_size, evolutionaryAlgorithm.getPopulation().size());
        }

        for (int i = 0; i < p.children_bred_per_generation; ++i) {
            evolutionaryAlgorithm.getNext();
            BOOST_CHECK_EQUAL(p.population_size + p.children_bred_per_generation, evolutionaryAlgorithm.getPopulation().size());
        }
    }

    BOOST_FIXTURE_TEST_CASE(PreferFitterNetworksTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 8;
        p.crossover_probability = 1;
        p.mutation_probability = 0.5;
        p.input_size = 2;
        p.hidden_layers = 2;
        p.output_size = 1;
        p.weight_variance = 10;

        EvolutionaryAlgorithm evolutionaryAlgorithm(p);

        for (int i = 0; i < p.population_size; ++i)
            evolutionaryAlgorithm.getNext()->setFitness(i);
        evolutionaryAlgorithm.getNext();

        bool contains_eight = false;
        bool contains_nine = false;
        for (auto& individual: evolutionaryAlgorithm.getPopulation()) {
            contains_eight = contains_eight || individual->getFitness() == 8;
            contains_nine = contains_nine || individual->getFitness() == 9;
        }

        BOOST_ASSERT(contains_eight);
        BOOST_ASSERT(contains_nine);
    }

    BOOST_FIXTURE_TEST_CASE(ImproveResultsTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 5;
        p.crossover_probability = 1;
        p.mutation_probability = 0.5;
        p.input_size = 2;
        p.hidden_layers = 2;
        p.output_size = 1;
        p.weight_variance = 10.0;

        EvolutionaryAlgorithm evolutionaryAlgorithm(p);

        int i = 0;
        PNeuralNetwork current = evolutionaryAlgorithm.getNext();
        while (current->getFitness() < 3.50) {
            trainXOR(current);
            current = evolutionaryAlgorithm.getNext();

            if (++i % 500 == 0) {
                std::cout << "\rBest fit: " << evolutionaryAlgorithm.getPopulation()[0]->getFitness() << std::flush;
            }
        }

        std::cout << "\rBest fit: " << evolutionaryAlgorithm.getPopulation()[0]->getFitness() << std::flush;
    }

    BOOST_FIXTURE_TEST_CASE(SerializationTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 5;
        p.crossover_probability = 1;
        p.mutation_probability = 0.5;
        p.input_size = 5;
        p.hidden_layers = 5;
        p.output_size = 5;
        p.weight_variance = 50.0;

        EvolutionaryAlgorithm serialized_ea(p);

        serialized_ea.save("EvolutionaryAlgorithmTest.mg");

        EvolutionaryAlgorithm deserialized_ea;
        deserialized_ea.load("EvolutionaryAlgorithmTest.mg");

        PNeuralNetwork serialized_nn = serialized_ea.getNext();
        PNeuralNetwork deserialized_nn = deserialized_ea.getNext();

        Matrix input = {1, 1, 1, 1, 1};
        for (int i = 0; i < p.population_size; ++i) {
            serialized_nn->feedForward(input);
            deserialized_nn->feedForward(input);

            Matrix expected = serialized_nn->getOutput();
            Matrix actual = deserialized_nn->getOutput();

            serialized_nn = serialized_ea.getNext();
            deserialized_nn = deserialized_ea.getNext();

            BOOST_ASSERT(is_close(expected, actual, 0.0001));
        }
    }

BOOST_AUTO_TEST_SUITE_END()
