//
// Created by fajqa on 25.03.17.
//

#include "Connection.h"

int Connection::connection_counter = 0;
double Connection::weight_variance = 5.0;

int Connection::getOrderNumber() const {
    return order_number;
}

const std::shared_ptr<Neuron> &Connection::getInput() const {
    return input;
}

const std::shared_ptr<Neuron> &Connection::getOutput() const {
    return output;
}

bool Connection::isEnabled() const {
    return enabled;
}

double Connection::getWeight() const {
    return weight;
}

Connection::Connection(const std::shared_ptr<Neuron> &input,
                       const std::shared_ptr<Neuron> &output) : input(input),
                                                                  output(output) {
    connection_counter++;
    order_number = connection_counter;
    enabled = true;
    randomizeWeight();
}

void Connection::randomizeWeight() {
    double f = (double)rand() / RAND_MAX;
    weight =  (2 * f * weight_variance) - weight_variance;
}

bool Connection::operator==(const Connection &rhs) const {
    return order_number == rhs.order_number;
}

bool Connection::operator!=(const Connection &rhs) const {
    return !(rhs == *this);
}
