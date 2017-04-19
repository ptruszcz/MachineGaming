#include <gtest/gtest.h>
#include "Gene.h"
#include "Neuron.h"
#include "Connection.h"

TEST(GeneTest, InheritedCounterTest) {
    Neuron neuron1(0);
    Neuron neuron2(0);

    Connection connection(neuron1, neuron2);

    ASSERT_EQ(2, Neuron::howMany());
    ASSERT_EQ(0, neuron1.getId());
    ASSERT_EQ(1, neuron2.getId());

    ASSERT_EQ(1, Connection::howMany());
    ASSERT_EQ(0, connection.getId());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}