#define BOOST_TEST_MODULE "CounterTest"
#include <boost/test/unit_test.hpp>
#include "Counter.hpp"
#include "Neuron.h"
#include "Connection.h"

#include <fstream>

BOOST_AUTO_TEST_SUITE(CounterTest)
    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    typedef Counter<void> TestCounter;
    typedef std::unique_ptr<TestCounter> PTestCounter;

    static void serialize(const PTestCounter &test_counter) {
        std::ofstream ofs("CounterTest.mg");
        boost::archive::text_oarchive oa(ofs);
        oa << *test_counter;
    }

    static PTestCounter deserialize() {
        PTestCounter test_counter = std::make_unique<TestCounter>();
        std::ifstream ifs("CounterTest.mg");
        boost::archive::text_iarchive ia(ifs);
        ia >> *test_counter;
        return test_counter;
    }

    BOOST_FIXTURE_TEST_CASE(SerializationAndDeserializationTest, F) {
        // Two counter objects created before serialization.
        PTestCounter counter_object_one = std::make_unique<TestCounter>();
        PTestCounter counter_object_two = std::make_unique<TestCounter>();

        size_t expected = TestCounter::getCount();
        serialize(counter_object_one);
        PTestCounter counter_object_three = std::make_unique<TestCounter>();

        // Should be independent from number of deserialization calls.
        PTestCounter counter_object_four = deserialize();
        PTestCounter counter_object_five = deserialize();
        size_t actual = TestCounter::getCount();

        BOOST_CHECK_EQUAL(expected, actual);
    }

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

BOOST_AUTO_TEST_SUITE_END()