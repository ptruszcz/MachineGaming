//
// Created by fajqa on 23.03.17.
//

#include <gtest/gtest.h>
#include "Genotype.h"
#include "Phenotype.h"


TEST(PhenotypeTest, ConstructorTest) {
    Genotype genotype(10,1,15);
    Phenotype phenotype1(genotype);
    Phenotype phenotype2(genotype);

    ASSERT_EQ(phenotype1, phenotype2);

    genotype.mutate(ADD_NEURON);
    Phenotype phenotype3(genotype);

    ASSERT_NE(phenotype1, phenotype3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}