#include <boost/test/unit_test.hpp>
#include "Genome.h"
#include "Phenome.h"

BOOST_AUTO_TEST_SUITE(PhenomeTest)
    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    BOOST_FIXTURE_TEST_CASE(ConstructorTest, F) {
        Genome genome(10,1,15);
        Phenome expected(genome);
        Phenome actual(genome);

        BOOST_CHECK_EQUAL(expected, actual);
    }

    BOOST_FIXTURE_TEST_CASE(AddedNeuronTest, F) {
        Genome genome(10,1,15);
        Phenome not_expected(genome);

        genome.mutate(ADD_NEURON);
        Phenome actual(genome);

        BOOST_CHECK_NE(not_expected, actual);
    }

    BOOST_FIXTURE_TEST_CASE(CreateFromCrossoverGenome, F) {
        Genome parentA(1,1,1);
        Genome parentB(parentA);

        parentA.mutate(ADD_NEURON);
        parentB.mutate(ADD_NEURON);

        Phenome parentA_phenome(parentA);
        Phenome parentB_phenome(parentB);

        Genome child = *Genome::crossover(parentA, parentB);

        Phenome child_phenome(child);

        BOOST_CHECK_NE(parentA_phenome, child_phenome);
        BOOST_CHECK_NE(parentB_phenome, child_phenome);

        BOOST_CHECK_EQUAL(5, child.getNeurons().size());
    }
    
BOOST_AUTO_TEST_SUITE_END()