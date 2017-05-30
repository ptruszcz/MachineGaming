#define BOOST_TEST_MODULE "GenotypeTest"
#include <boost/test/unit_test.hpp>
#include <fstream>
#include "Genotype.hpp"
#include "Neuron.h"
#include "Connection.h"

BOOST_AUTO_TEST_SUITE(GenotypeTest)

    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    static void serialize(Genotype<Connection> genotypes[],
                          std::string filename) {
        std::ofstream ofs(filename);
        boost::archive::text_oarchive oa(ofs);
        oa << genotypes[0];
        oa << genotypes[1];
    }

    static void deserialize(Genotype<Connection> genotypes[],
                                      std::string filename) {
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia >> genotypes[0];
        ia >> genotypes[1];
    }

    BOOST_FIXTURE_TEST_CASE(InsertNeuronTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(3);

        Genotype<Neuron> neurons;
        neurons.insert(neuron1);
        neurons.insert(neuron2);
        neurons.insert(neuron4);

        Neurons genes = neurons.getGenes();

        BOOST_CHECK_EQUAL(3, genes.size());
    }

    BOOST_FIXTURE_TEST_CASE(EraseNeuronTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(2);

        Genotype<Neuron> neurons;
        neurons.insert(neuron1);
        neurons.insert(neuron2);
        neurons.insert(neuron4);

        neurons.erase(neuron2);

        Neurons genes = neurons.getGenes();

        BOOST_CHECK_EQUAL(2, genes.size());
    }

    BOOST_FIXTURE_TEST_CASE(CrossoverNeuronTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(2);

        Genotype<Neuron> neurons1;
        neurons1.insert(neuron1);
        neurons1.insert(neuron2);
        neurons1.insert(neuron4);

        Genotype<Neuron> neurons2;
        neurons2.insert(neuron1);
        neurons2.insert(neuron3);
        neurons2.insert(neuron4);

        PGenotype<Neuron> child_neurons = Genotype<Neuron>::crossover(neurons1, neurons2);

        Neurons genes = child_neurons->getGenes();

        BOOST_CHECK_EQUAL(4, genes.size());
        BOOST_CHECK_EQUAL(4, Neuron::getCount());

        BOOST_CHECK_EQUAL(neuron1, genes[0]);
        BOOST_CHECK_EQUAL(neuron2, genes[1]);
        BOOST_CHECK_EQUAL(neuron3, genes[2]);
        BOOST_CHECK_EQUAL(neuron4, genes[3]);
    }

    BOOST_FIXTURE_TEST_CASE(InsertConnectionTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(2);

        PConnection connection1 = std::make_shared<Connection>(neuron1, neuron2);
        PConnection connection2 = std::make_shared<Connection>(neuron1, neuron3);
        PConnection connection3 = std::make_shared<Connection>(neuron2, neuron4);
        PConnection connection4 = std::make_shared<Connection>(neuron3, neuron4);

        Genotype<Connection> connections;
        connections.insert(connection2);
        connections.insert(connection4);

        Connections genes = connections.getGenes();

        BOOST_CHECK_EQUAL(2, genes.size());
    }

    BOOST_FIXTURE_TEST_CASE(EraseConnectionTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(2);

        PConnection connection1 = std::make_shared<Connection>(neuron1, neuron2);
        PConnection connection2 = std::make_shared<Connection>(neuron1, neuron3);
        PConnection connection3 = std::make_shared<Connection>(neuron2, neuron4);
        PConnection connection4 = std::make_shared<Connection>(neuron3, neuron4);

        Genotype<Connection> connections;
        connections.insert(connection2);
        connections.insert(connection4);

        connections.erase(connection2);

        Connections genes = connections.getGenes();

        BOOST_CHECK_EQUAL(1, genes.size());
    }

    BOOST_FIXTURE_TEST_CASE(CrossoverConnectionTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(2);

        PConnection connection1 = std::make_shared<Connection>(neuron1, neuron2);
        PConnection connection2 = std::make_shared<Connection>(neuron1, neuron3);
        PConnection connection3 = std::make_shared<Connection>(neuron2, neuron4);
        PConnection connection4 = std::make_shared<Connection>(neuron3, neuron4);

        Genotype<Connection> connections1;
        connections1.insert(connection1);
        connections1.insert(connection3);

        Genotype<Connection> connections2;
        connections2.insert(connection2);
        connections2.insert(connection4);

        Genotype<Connection> child_connections = *Genotype<Connection>::crossover(connections1, connections2)->clone();

        Connections genes = child_connections.getGenes();

        BOOST_CHECK_EQUAL(4, genes.size());
        BOOST_CHECK_EQUAL(4, Connection::getCount());

        BOOST_CHECK_EQUAL(connection1->getId(), genes[0]->getId());
        BOOST_CHECK_EQUAL(connection2->getId(), genes[1]->getId());
        BOOST_CHECK_EQUAL(connection3->getId(), genes[2]->getId());
        BOOST_CHECK_EQUAL(connection4->getId(), genes[3]->getId());
    }

    BOOST_FIXTURE_TEST_CASE(SerializationTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(2);

        PConnection connection1 = std::make_shared<Connection>(neuron1, neuron2);
        PConnection connection2 = std::make_shared<Connection>(neuron1, neuron3);
        PConnection connection3 = std::make_shared<Connection>(neuron2, neuron4);
        PConnection connection4 = std::make_shared<Connection>(neuron3, neuron4);


        Genotype<Connection> expected[2];

        expected[0].insert(connection1);
        expected[0].insert(connection2);
        expected[0].insert(connection3);
        expected[0].insert(connection4);

        expected[1].insert(connection1);
        expected[1].insert(connection2);
        expected[1].insert(connection3);
        expected[1].insert(connection4);

        serialize(expected, "GenotypeTest.mg");

        Genotype<Connection> actual[2];

        deserialize(actual, "GenotypeTest.mg");

        BOOST_CHECK_EQUAL(expected[0], expected[1]);
        BOOST_CHECK_EQUAL(actual[0], actual[1]);

        Connections expected_connections1 = expected[0].getGenes();
        Connections expected_connections2 = expected[1].getGenes();
        Connections actual_connections1 = actual[0].getGenes();
        Connections actual_connections2 = actual[1].getGenes();

        for (int i = 0; i < 4; ++i) {
            BOOST_CHECK_EQUAL(*expected_connections1.at(i), *actual_connections1.at(i));
            BOOST_CHECK_EQUAL(*expected_connections2.at(i), *actual_connections2.at(i));
        }
}

BOOST_AUTO_TEST_SUITE_END()