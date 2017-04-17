#include "Connection.h"

Random Connection::random = Random();
int Connection::counter = 0;
double Connection::weight_variance = 5.0;

int Connection::getCounter() {
    return counter;
}

void Connection::resetCounter() {
    Connection::counter = 0;
}

double Connection::getWeightVariance() {
    return weight_variance;
}

void Connection::setWeightVariance(double weight_variance) {
    Connection::weight_variance = weight_variance;
}

int Connection::getOrderNumber() const {
    return order_number;
}

const PNeuron &Connection::getInput() const {
    return input;
}

const PNeuron &Connection::getOutput() const {
    return output;
}

bool Connection::isEnabled() const {
    return enabled;
}

double Connection::getWeight() const {
    return weight;
}

Connection::Connection(const PNeuron &input,
                       const PNeuron &output) : input(input),
                                                output(output) {
    counter++;
    order_number = counter;
    enabled = true;
    randomizeWeight();
}

void Connection::randomizeWeight() {
    weight = random.next(-weight_variance, weight_variance);
}

bool Connection::operator==(const Connection &rhs) const {
    return order_number == rhs.order_number &&
            weight == rhs.weight &&
            enabled == rhs.enabled &&
            input == rhs.input &&
            output == rhs.output;
}

bool Connection::operator!=(const Connection &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Connection &connection) {
    os << "[No.: " << connection.order_number << " In " << *connection.input << " Out "
       << *connection.output << " Weight " << connection.weight << " Enabled " << connection.enabled << "]";
    return os;
}
