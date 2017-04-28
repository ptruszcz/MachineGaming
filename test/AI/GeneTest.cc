#include <boost/test/unit_test.hpp>
#include <Neuron.h>
#include <Connection.h>

BOOST_AUTO_TEST_SUITE(GeneTest)

BOOST_AUTO_TEST_CASE(InheritedCounterTest) {
    PNeuron neuron1 = std::make_shared<Neuron>(Neuron(0));
    PNeuron neuron2 = std::make_shared<Neuron>(Neuron(0));
    PGene neuron3 = neuron1->clone();

    Connection connection(neuron1, neuron2);

    BOOST_CHECK_EQUAL(2, Neuron::howMany());
    BOOST_CHECK_EQUAL(0, neuron1->getId());
    BOOST_CHECK_EQUAL(1, neuron2->getId());

    BOOST_CHECK_EQUAL(1, Connection::howMany());
    BOOST_CHECK_EQUAL(0, connection.getId());
}

BOOST_AUTO_TEST_SUITE_END()