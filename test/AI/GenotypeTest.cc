//
// Created by fajqa on 31.03.17.
//

#include <gtest/gtest.h>
#include "Genotype.h"
#include "Connection.h"

template class std::vector<PNeuron>;
template class std::vector<Connection>;

class GenotypeTest: public testing::Test {
public:
    virtual void SetUp() {
        Neuron::resetCounter();
        Connection::resetCounter();
    }

    virtual void TearDown() {}
};


TEST_F(GenotypeTest, SimpleGenotypeTest) {
    Genotype genotype1(5, 1, 10);
    ASSERT_EQ(16, genotype1.getNeurons().size());
    ASSERT_EQ(15, genotype1.getConnections().size());


    Genotype genotype2(1, 1, 1);
    ASSERT_EQ(3, genotype2.getNeurons().size());
    ASSERT_EQ(2, genotype2.getConnections().size());
}

TEST_F(GenotypeTest, CopyingConstuctorTest) {
    Genotype genotype1(5, 3, 10);
    Genotype genotype2(genotype1);
    ASSERT_EQ(genotype1, genotype2);
}

TEST_F(GenotypeTest, ComplexGenotypeTest) {
    Genotype genotype(50, 10, 20);
    ASSERT_EQ(50 + 10 + 20, genotype.getNeurons().size());
    ASSERT_EQ(50 + 9 + 20, genotype.getConnections().size());
}

TEST_F(GenotypeTest, NeuronAddingTest) {
    Genotype genotype1(50, 10, 20);
    Genotype genotype2(genotype1);
    genotype2.mutate(ADD_NEURON);
    ASSERT_NE(genotype1, genotype2);
}

TEST_F(GenotypeTest, ConnectionAddingTest) {
    Genotype genotype1(50, 10, 20);
    Genotype genotype2(genotype1);
    genotype2.mutate(ADD_CONNECTION);
    ASSERT_NE(genotype1, genotype2);
}

TEST_F(GenotypeTest, WeightRandomizationTest) {
    Genotype genotype1(50, 10, 20);
    Genotype genotype2(genotype1);
    genotype2.mutate(DISABLE_CONNECTION);

    bool disabled_connection_flag = false; //true if at least one connection is disabled
    for(Connection c : genotype2.getConnections())
        if(!c.isEnabled())
            disabled_connection_flag = true;

    ASSERT_TRUE(disabled_connection_flag);
    ASSERT_NE(genotype1, genotype2);
}

TEST_F(GenotypeTest, ConnectionDisablingTest) {
    Genotype genotype1(50, 10, 20);
    Genotype genotype2(genotype1);
    genotype2.mutate(RANDOMIZE_WEIGHT);
    ASSERT_NE(genotype1, genotype2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
