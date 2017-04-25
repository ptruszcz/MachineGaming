#define BOOST_TEST_MODULE GeneTest
#include <boost/test/unit_test.hpp>
#include "Gene.h"
#include "Neuron.h"
#include "Connection.h"

BOOST_AUTO_TEST_CASE(InheritedCounterTest) {
    PNeuron neuron1 = std::make_shared<Neuron>(Neuron(0));
    PNeuron neuron2 = std::make_shared<Neuron>(Neuron(0));
    PGene neuron3 = neuron1->clone();

    Connection connection(neuron1, neuron2);

    BOOST_TEST(2 == Neuron::howMany());
    BOOST_TEST(0 == neuron1->getId());
    BOOST_TEST(1 == neuron2->getId());

    BOOST_TEST(1 == Connection::howMany());
    BOOST_TEST(0 == connection.getId());
}