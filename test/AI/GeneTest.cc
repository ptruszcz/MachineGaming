#include <gtest/gtest.h>
#include "Gene.h"
#include "Neuron.h"
#include "Connection.h"

TEST(GeneTest, InheritedCounterTest) {
    PNeuron neuron1 = std::make_shared<Neuron>(Neuron(0));
    PNeuron neuron2 = std::make_shared<Neuron>(Neuron(0));
    PGene neuron3 = neuron1->clone();

    Connection connection(neuron1, neuron2);

    ASSERT_EQ(2, Neuron::howMany());
    ASSERT_EQ(0, neuron1->getId());
    ASSERT_EQ(1, neuron2->getId());

    ASSERT_EQ(1, Connection::howMany());
    ASSERT_EQ(0, connection.getId());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}