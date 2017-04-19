#include <gtest/gtest.h>
#include "Genome.h"
#include "Connection.h"

template class std::vector<PNeuron>;
template class std::vector<Connection>;

class GenomeTest: public testing::Test {
public:
    virtual void SetUp() {
        Neuron::resetCounter();
        Connection::resetCounter();
    }

    virtual void TearDown() {}
};


TEST_F(GenomeTest, SimpleGenomeTest) {
    Genome genome1(5, 1, 10);
    ASSERT_EQ(16, genome1.getNeurons().size());
    ASSERT_EQ(15, genome1.getConnections().size());


    Genome genome2(1, 1, 1);
    ASSERT_EQ(3, genome2.getNeurons().size());
    ASSERT_EQ(2, genome2.getConnections().size());
}

TEST_F(GenomeTest, CopyingConstuctorTest) {
    Genome genome1(5, 3, 10);
    Genome genome2(genome1);
    ASSERT_EQ(genome1, genome2);
}

TEST_F(GenomeTest, ComplexGenomeTest) {
    Genome genome(50, 10, 20);
    ASSERT_EQ(50 + 10 + 20, genome.getNeurons().size());
    ASSERT_EQ(50 + 9 + 20, genome.getConnections().size());
}

TEST_F(GenomeTest, NeuronAddingTest) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);
    genome2.mutate(ADD_NEURON);
    ASSERT_NE(genome1, genome2);
}

TEST_F(GenomeTest, ConnectionAddingTest) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);
    genome2.mutate(ADD_CONNECTION);
    ASSERT_NE(genome1, genome2);
}

TEST_F(GenomeTest, WeightRandomizationTest) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);
    genome2.mutate(DELETE_CONNECTION);

//    bool disabled_connection_flag = false; //true if at least one connection is disabled
/*    for(Connection c: genome2.getConnections())
        if(!c.isEnabled())
            disabled_connection_flag = true;*/

//    ASSERT_TRUE(disabled_connection_flag);
    //ASSERT_NE(genome1, genome2);
}

TEST_F(GenomeTest, ConnectionDisablingTest) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);
    genome2.mutate(RANDOMIZE_WEIGHT);
    ASSERT_NE(genome1, genome2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
