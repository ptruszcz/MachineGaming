//
// Created by fajqa on 23.03.17.
//

#include <gtest/gtest.h>
#include "Genome.h"
#include "Phenome.h"


TEST(PhenomeTest, ConstructorTest) {
    Genome genotype(10,1,15);
    Phenome phenome1(genotype);
    Phenome phenome2(genotype);

    ASSERT_EQ(phenome1, phenome2);

    genotype.mutate(ADD_NEURON);
    Phenome phenome3(genotype);

    ASSERT_NE(phenome1, phenome3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}