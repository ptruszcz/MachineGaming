//
// Created by fajqa on 25.03.17.
//

#include "Connection.h"

int Connection::getOrderNumber() const {
    return order_number;
}

const boost::shared_ptr<Neuron> &Connection::getInput() const {
    return input;
}

const boost::shared_ptr<Neuron> &Connection::getOutput() const {
    return output;
}

bool Connection::isEnabled() const {
    return enabled;
}

double Connection::getWeight() const {
    return weight;
}

Connection::Connection(const boost::shared_ptr<Neuron> &input,
                       const boost::shared_ptr<Neuron> &output) : input(input),
                                                                  output(output) {
    counter++;
    order_number = counter;
    enabled = true;
    randomizeWeight();
}

void Connection::randomizeWeight() {
    double f = (double)rand() / RAND_MAX;
    weight =  (2 * f * weight_variance) - weight_variance;
}
