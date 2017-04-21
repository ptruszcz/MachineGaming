#include <gtest/gtest.h>
#include "Genotype.h"
#include "Gene.h"
#include "Neuron.h"
#include "Connection.h"


class GenotypeTest: public testing::Test {
public:
    virtual void SetUp() {
        Neuron::resetCounter();
        Connection::resetCounter();
    }

    virtual void TearDown() {}
};

TEST_F(GenotypeTest, InsertNeuronTest) {
    PNeuron neuron1 = std::make_shared<Neuron>(0);
    PNeuron neuron2 = std::make_shared<Neuron>(1);
    PNeuron neuron3 = std::make_shared<Neuron>(1);
    PNeuron neuron4 = std::make_shared<Neuron>(3);

    Genotype neurons;
    neurons.insert(neuron1);
    neurons.insert(neuron2);
    neurons.insert(neuron4);

    std::vector<PGene> genes = neurons.getGenes();

    ASSERT_EQ(3, genes.size());
}

TEST_F(GenotypeTest, EraseNeuronTest) {
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

    ASSERT_EQ(2, genes.size());
}

TEST_F(GenotypeTest, CrossoverNeuronTest) {
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

    Genotype child_neurons = Genotype::crossover(neurons1, neurons2);

    std::vector<PGene> genes = child_neurons.getGenes();

    ASSERT_EQ(4, genes.size());
    ASSERT_EQ(4, Neuron::howMany());
}

TEST_F(GenotypeTest, InsertConnectionTest) {
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

    ASSERT_EQ(2, genes.size());
}

TEST_F(GenotypeTest, EraseConnectionTest) {
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

    ASSERT_EQ(1, genes.size());
}

TEST_F(GenotypeTest, CrossoverConnectionTest) {
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

    Genotype child_connections = Genotype::crossover(connections1, connections2);

    std::vector<PGene> genes = child_connections.getGenes();

    ASSERT_EQ(4, genes.size());
    ASSERT_EQ(4, Connection::howMany());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}