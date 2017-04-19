#include "Connection.h"

Random Connection::random = Random();
double Connection::weight_variance = 5.0;

const PNeuron &Connection::getInput() const {
    return input;
}

const PNeuron &Connection::getOutput() const {
    return output;
}

double Connection::getWeight() const {
    return weight;
}
Connection::Connection(const Neuron &input,
                       const Neuron &output) : Counter(), Gene(howMany()) {
    this->input = std::make_shared<Neuron>(input);
    this->output = std::make_shared<Neuron>(output);
    randomizeWeight();
}

void Connection::mutate(MutationType mutation_type) {
    //TODO
    randomizeWeight();
}

void Connection::randomizeWeight() {
    weight = random.next(-weight_variance, weight_variance);
}

bool Connection::operator==(const Connection &rhs) const {
    return id == rhs.id &&
            weight == rhs.weight &&
            input == rhs.input &&
            output == rhs.output;
}

bool Connection::operator!=(const Connection &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Connection &connection) {
    os << "[No.: " << connection.id << " In " << *connection.input << " Out "
       << *connection.output << " Weight " << connection.weight << "]";
    return os;
}