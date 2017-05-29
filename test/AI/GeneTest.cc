#include <boost/test/unit_test.hpp>
#include <Neuron.h>
#include <Connection.h>

BOOST_AUTO_TEST_SUITE(GeneTest)
    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    BOOST_FIXTURE_TEST_CASE(InheritedCounterTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(0);
        PGene neuron3 = neuron1->clone();

        Connection connection(neuron1, neuron2);

        BOOST_CHECK_EQUAL(2, Neuron::getCount());
        BOOST_CHECK_EQUAL(0, neuron1->getId());
        BOOST_CHECK_EQUAL(1, neuron2->getId());

        BOOST_CHECK_EQUAL(1, Connection::getCount());
        BOOST_CHECK_EQUAL(0, connection.getId());
    }

    BOOST_FIXTURE_TEST_CASE(CloneConnectionTest, F) {
        PNeuron neuron1 = std::make_shared<Neuron>(0);
        PNeuron neuron2 = std::make_shared<Neuron>(0);

        Connection connection1(neuron1, neuron2);
        PConnection connection2 = std::static_pointer_cast<Connection>(connection1.clone());


        BOOST_CHECK_EQUAL(2, Neuron::getCount());
        BOOST_CHECK_EQUAL(0, neuron1->getId());
        BOOST_CHECK_EQUAL(1, neuron2->getId());
        BOOST_CHECK_EQUAL(0, connection1.getInput()->getId());
        BOOST_CHECK_EQUAL(1, connection1.getOutput()->getId());

        BOOST_CHECK_EQUAL(1, Connection::getCount());
        BOOST_CHECK_EQUAL(0, connection1.getId());
        BOOST_CHECK_EQUAL(0, connection2->getId());

        BOOST_CHECK_EQUAL(connection1.getInput(), connection2->getInput());
        BOOST_CHECK_EQUAL(connection1.getOutput(), connection2->getOutput());
    }

BOOST_AUTO_TEST_SUITE_END()