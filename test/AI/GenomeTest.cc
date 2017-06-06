#define BOOST_TEST_MODULE "GenomeTest"
#include <boost/test/unit_test.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include "Genome.h"

BOOST_AUTO_TEST_SUITE(GenomeTest)

    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    static void serialize(PGenome genomes[],
                          std::string filename) {
        std::ofstream ofs(filename);
        boost::archive::text_oarchive oa(ofs);
        oa << genomes[0];
        oa << genomes[1];
    }

    static void deserialize(PGenome genomes[],
                            std::string filename) {
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia >> genomes[0];
        ia >> genomes[1];
    }

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
        BOOST_CHECK_EQUAL(genome1, genome2);
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
        Genome genome1(100, 1, 100);
        Genome genome2(genome1);

        for (int i=0; i<100; ++i) {
            genome2.mutate(ADD_NEURON);
        }


        genome2.mutate(ADD_CONNECTION);
        Connections genes1 = genome1.getConnections();
        Connections genes2 = genome2.getConnections();

        BOOST_ASSERT(genes1.size() < genes2.size());
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
        BOOST_CHECK_EQUAL(genome1, genome2);
    }

    BOOST_FIXTURE_TEST_CASE(SerializationTest, F) {
        PGenome serialized[2];
        serialized[0] = std::make_unique<Genome>(5, 5, 5);
        serialized[1] = std::make_unique<Genome>(*serialized[0]);

        serialize(serialized, "GenomeTest.mg");

        PGenome deserialized[2];

        deserialize(deserialized, "GenomeTest.mg");

        BOOST_CHECK_EQUAL(*serialized[0], *serialized[1]);
        BOOST_CHECK_EQUAL(*deserialized[0], *deserialized[1]);

        deserialized[0]->mutate(ADD_NEURON);
        deserialized[1]->mutate(ADD_NEURON);
    }

BOOST_AUTO_TEST_SUITE_END()