#include <boost/test/unit_test.hpp>
#include "EvolutionaryAlgorithm.h"

BOOST_AUTO_TEST_SUITE(EvolutionaryAlgorithmTest)
    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    BOOST_FIXTURE_TEST_CASE(GenerationSizeTest, F) {
        EvolutionaryAlgorithmParameters p;
        p.population_size = 10;
        p.children_bred_per_generation = 2;
        p.crossover_probability = 1;

        EvolutionaryAlgorithm evolutionaryAlgorithm(p);
        BOOST_CHECK_EQUAL(p.population_size, evolutionaryAlgorithm.getCurrentGeneration().size());

        evolutionaryAlgorithm.breed();
        BOOST_CHECK_EQUAL(p.population_size + p.children_bred_per_generation,
                          evolutionaryAlgorithm.getCurrentGeneration().size());

        evolutionaryAlgorithm.removeWeakestIndividuals();
        BOOST_CHECK_EQUAL(p.population_size, evolutionaryAlgorithm.getCurrentGeneration().size());
    }

BOOST_AUTO_TEST_SUITE_END()