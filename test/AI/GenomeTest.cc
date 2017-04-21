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
    Genome genome1(1, 1, 1);
    Genome genome2(genome1);
    ASSERT_NE(genome1, genome2);
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

TEST_F(GenomeTest, ConnectionDeletingTest) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);

    genome2.mutate(DELETE_CONNECTION);
    Connections genes1 = genome1.getConnections();
    Connections genes2 = genome2.getConnections();

    ASSERT_TRUE(genes1.size() > genes2.size());
    ASSERT_NE(genome1, genome2);
}

TEST_F(GenomeTest, WeightRandomizationTest) {
    Genome genome1(50, 10, 20);
    Genome genome2(genome1);
    genome2.mutate(RANDOMIZE_WEIGHT);
    ASSERT_NE(genome1, genome2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
