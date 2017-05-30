#define BOOST_TEST_MODULE "GeneTest"
#include <boost/test/unit_test.hpp>
#include <fstream>

#include "Neuron.h"
#include "Connection.h"

BOOST_AUTO_TEST_SUITE(GeneTest)

    struct F {
        F() {
            Neuron::resetCounter();
            Connection::resetCounter();
        }
    };

    static void serialize(const PNeuron &neuron, std::string filename) {
        std::ofstream ofs(filename);
        boost::archive::text_oarchive oa(ofs);
        oa << *neuron;
    }

    static PNeuron deserializeNeuron(std::string filename) {
        PNeuron neuron = std::make_unique<Neuron>();
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia >> *neuron;
        return neuron;
    }

    static void serialize(const PConnection &input_connection,
                          const PConnection &output_connection,
                          std::string filename) {
        std::ofstream ofs(filename);
        boost::archive::text_oarchive oa(ofs);
        oa << input_connection;
        oa << output_connection;
    }

    static void deserializeConnection(PConnection connections[],
                                      std::string filename) {
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia >> connections[0];
        ia >> connections[1];
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

    BOOST_FIXTURE_TEST_CASE(SerializeNeuronTest, F) {
        PNeuron expected1 = std::make_shared<Neuron>(0);
        PNeuron expected2 = std::make_shared<Neuron>(1);

        serialize(expected1, "Neuron1.mg");
        serialize(expected2, "Neuron2.mg");

        PNeuron actual1 = deserializeNeuron("Neuron1.mg");
        PNeuron actual2 = deserializeNeuron("Neuron2.mg");

        BOOST_CHECK_EQUAL(*expected1, *actual1);
        BOOST_CHECK_EQUAL(*expected2, *actual2);
    }

    BOOST_FIXTURE_TEST_CASE(SerializeConnectionTest, F) {
        PNeuron input_neuron = std::make_shared<Neuron>(0);
        PNeuron hidden_neuron = std::make_shared<Neuron>(1);
        PNeuron output_neuron = std::make_shared<Neuron>(2);

        PConnection expected_input_connection = std::make_shared<Connection>(input_neuron, hidden_neuron);
        PConnection expected_output_connection = std::make_shared<Connection>(hidden_neuron, output_neuron);

        serialize(expected_input_connection,
                  expected_output_connection,
                  "ConnectionTest.mg");

        PConnection connections[2];
        deserializeConnection(connections, "ConnectionTest.mg");

        PConnection actual_input_connection = connections[0];
        PConnection actual_output_connection = connections[1];

        BOOST_CHECK_EQUAL(*expected_input_connection, *actual_input_connection);
        BOOST_CHECK_EQUAL(*expected_output_connection, *actual_output_connection);

        BOOST_CHECK_EQUAL(actual_input_connection->getOutput(), actual_output_connection->getInput());
    }

BOOST_AUTO_TEST_SUITE_END()