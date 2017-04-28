#include <boost/test/unit_test.hpp>
#include "Genome.h"
#include "Phenome.h"

BOOST_AUTO_TEST_SUITE(PhenomeTest)

BOOST_AUTO_TEST_CASE(ConstructorTest) {
    Genome genotype(10,1,15);
    Phenome expected(genotype);
    Phenome actual(genotype);

    BOOST_CHECK_EQUAL(expected, actual);
}

BOOST_AUTO_TEST_CASE(AddedNeuronTest) {
    Genome genotype(10,1,15);
    Phenome not_expected(genotype);
        
    genotype.mutate(ADD_NEURON);
    Phenome actual(genotype);

    BOOST_CHECK_NE(not_expected, actual);
}
    
BOOST_AUTO_TEST_SUITE_END()