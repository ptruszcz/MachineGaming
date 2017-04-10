//
// Created by fajqa on 23.03.17.
//

#include <gtest/gtest.h>
#include "Genotype.h"
#include "Phenotype.h"


TEST(PhenotypeTest, ConstructorTest) {
    Genotype genotype(10,1,15);
    genotype.mutate(ADD_NEURON);
    Phenotype phenotype(genotype);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}