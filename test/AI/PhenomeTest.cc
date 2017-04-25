#define BOOST_TEST_MODULE PhenomeTest
#include <boost/test/unit_test.hpp>
#include "Genome.h"
#include "Phenome.h"


BOOST_AUTO_TEST_CASE(ConstructorTest) {
    Genome genotype(10,1,15);
    Phenome phenome1(genotype);
    Phenome phenome2(genotype);

    BOOST_ASSERT(phenome1 == phenome2);

    genotype.mutate(ADD_NEURON);
    Phenome phenome3(genotype);

    BOOST_ASSERT(phenome1 != phenome3);
}