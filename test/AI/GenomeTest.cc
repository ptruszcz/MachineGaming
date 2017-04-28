#include <boost/test/unit_test.hpp>
#include "Genome.h"

BOOST_AUTO_TEST_SUITE(GenomeTest)

struct F {
    F() {
        Neuron::resetCounter(); 
        Connection::resetCounter();
    }
};

BOOST_FIXTURE_TEST_CASE(SimpleGenomeTest, F) {
    Genome genome1(5, 1, 10);
    BOOST_CHECK_EQUAL(16, genome1.getNeurons().size());
    BOOST_CHECK_EQUAL(15, genome1.getConnections().size());


    Genome genome2(1, 1, 1);
    BOOST_CHECK_EQUAL(3, genome2.getNeurons().size());
    BOOST_CHECK_EQUAL(2, genome2.getConnections().size());
}

BOOST_FIXTURE_TEST_CASE(CopyingConstuctorTest, F) {
    Genome genome1(1, 1, 1);
    Genome genome2(genome1);
    BOOST_CHECK_NE(genome1, genome2);
}

BOOST_FIXTURE_TEST_CASE(ComplexGenomeTest, F) {
    Genome genome(50, 10, 20);
    BOOST_CHECK_EQUAL(50 + 10 + 20, genome.getNeurons().size());
    BOOST_CHECK_EQUAL(50 + 9 + 20, genome.getConnections().size());
}

BOOST_FIXTURE_TEST_CASE(NeuronAddingTest, F) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);
    genome2.mutate(ADD_NEURON);
    BOOST_CHECK_NE(genome1, genome2);
}

BOOST_FIXTURE_TEST_CASE(ConnectionAddingTest, F) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);
    genome2.mutate(ADD_CONNECTION);
    BOOST_CHECK_NE(genome1, genome2);
}

BOOST_FIXTURE_TEST_CASE(ConnectionDeletingTest, F) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);

    genome2.mutate(DELETE_CONNECTION);
    Connections genes1 = genome1.getConnections();
    Connections genes2 = genome2.getConnections();

    BOOST_ASSERT(genes1.size() > genes2.size());
    BOOST_CHECK_NE(genome1, genome2);
}

BOOST_FIXTURE_TEST_CASE(WeightRandomizationTest, F) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);
    genome2.mutate(RANDOMIZE_WEIGHT);
    BOOST_CHECK_NE(genome1, genome2);
}

BOOST_AUTO_TEST_SUITE_END()