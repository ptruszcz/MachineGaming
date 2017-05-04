#include <boost/test/unit_test.hpp>
#include "Genotype.h"
#include "Neuron.h"
#include "Connection.h"

BOOST_AUTO_TEST_SUITE(GenotypeTest)

    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    BOOST_FIXTURE_TEST_CASE(InsertNeuronTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(3);

        Genotype neurons;
        neurons.insert(neuron1);
        neurons.insert(neuron2);
        neurons.insert(neuron4);

        std::vector<PGene> genes = neurons.getGenes();

        BOOST_CHECK_EQUAL(3, genes.size());
    }

    BOOST_FIXTURE_TEST_CASE(EraseNeuronTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(2);

        Genotype neurons;
        neurons.insert(neuron1);
        neurons.insert(neuron2);
        neurons.insert(neuron4);

        neurons.erase(neuron2);

        std::vector<PGene> genes = neurons.getGenes();

        BOOST_CHECK_EQUAL(2, genes.size());
    }

    BOOST_FIXTURE_TEST_CASE(CrossoverNeuronTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(1);
        PNeuron neuron3 = std::make_shared<Neuron>(1);
        PNeuron neuron4 = std::make_shared<Neuron>(2);

        Genotype neurons1;
        neurons1.insert(neuron1);
        neurons1.insert(neuron2);
        neurons1.insert(neuron4);

        Genotype neurons2;
        neurons2.insert(neuron1);
        neurons2.insert(neuron3);
        neurons2.insert(neuron4);

        PGenotype child_neurons = Genotype::crossover(neurons1, neurons2);

        std::vector<PGene> genes = child_neurons->getGenes();

        BOOST_CHECK_EQUAL(4, genes.size());
        BOOST_CHECK_EQUAL(4, Neuron::howMany());

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

        Genotype connections;
        connections.insert(connection2);
        connections.insert(connection4);

        std::vector<PGene> genes = connections.getGenes();

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

        Genotype connections;
        connections.insert(connection2);
        connections.insert(connection4);

        connections.erase(connection2);

        std::vector<PGene> genes = connections.getGenes();

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

        Genotype connections1;
        connections1.insert(connection1);
        connections1.insert(connection3);

        Genotype connections2;
        connections2.insert(connection2);
        connections2.insert(connection4);

        Genotype child_connections = *Genotype::crossover(connections1, connections2)->clone();

        std::vector<PGene> genes = child_connections.getGenes();

        BOOST_CHECK_EQUAL(4, genes.size());
        BOOST_CHECK_EQUAL(4, Connection::howMany());

        BOOST_CHECK_EQUAL(connection1->getId(), genes[0]->getId());
        BOOST_CHECK_EQUAL(connection2->getId(), genes[1]->getId());
        BOOST_CHECK_EQUAL(connection3->getId(), genes[2]->getId());
        BOOST_CHECK_EQUAL(connection4->getId(), genes[3]->getId());
    }

BOOST_AUTO_TEST_SUITE_END()