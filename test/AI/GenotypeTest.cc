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

TEST_F(GenotypeTest, InsertTest) {
    Neuron neuron1(0);
    Neuron neuron2(0);
    Neuron neuron3(0);
    Neuron neuron4(0);

    Genotype neurons;
    neurons.insert(std::make_shared<Neuron>(neuron1));
    neurons.insert(std::make_shared<Neuron>(neuron2));
    neurons.insert(std::make_shared<Neuron>(neuron4));

    std::vector<PGene> genes = neurons.getGenes();

    ASSERT_EQ(3, genes.size());
}

TEST_F(GenotypeTest, EraseTest) {
    Neuron neuron1(0);
    Neuron neuron2(0);
    Neuron neuron3(0);
    Neuron neuron4(0);

    Genotype neurons;
    neurons.insert(std::make_shared<Neuron>(neuron1));
    neurons.insert(std::make_shared<Neuron>(neuron2));
    neurons.insert(std::make_shared<Neuron>(neuron4));

    neurons.erase(std::make_shared<Neuron>(neuron2));

    std::vector<PGene> genes = neurons.getGenes();

    ASSERT_EQ(2, genes.size());
}

TEST_F(GenotypeTest, CrossoverTest) {
    Neuron neuron1(0);
    Neuron neuron2(0);
    Neuron neuron3(0);
    Neuron neuron4(0);

    Genotype neurons1;
    neurons1.insert(std::make_shared<Neuron>(neuron1));
    neurons1.insert(std::make_shared<Neuron>(neuron2));
    neurons1.insert(std::make_shared<Neuron>(neuron4));

    Genotype neurons2;
    neurons2.insert(std::make_shared<Neuron>(neuron1));
    neurons2.insert(std::make_shared<Neuron>(neuron3));
    neurons2.insert(std::make_shared<Neuron>(neuron4));

    Genotype child_neurons = Genotype::crossover(neurons1, neurons2);

    std::vector<PGene> genes = child_neurons.getGenes();

    ASSERT_EQ(4, genes.size());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}