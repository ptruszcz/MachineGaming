#include "Connection.h"

Random Connection::random = Random();
double Connection::weight_variance = 5.0;

Connection::Connection(const PNeuron &input,
                       const PNeuron &output) : Counter(), Gene(getCount()) {
    this->input_ = input;
    this->output_ = output;
    randomizeWeight();
}

Connection::Connection(const Connection &connection) : Counter(connection), Gene(connection) {
    this->input_ = connection.input_;
    this->output_ = connection.output_;
    this->weight_ = connection.weight_;
}

PGene Connection::clone() const {
    return std::make_shared<Connection>(*this);
}

void Connection::mutate(MutationType mutation_type) {
    switch (mutation_type) {
        case RANDOMIZE_WEIGHT:
            randomizeWeight();
            break;

        default:
            break;
    }
}

void Connection::randomizeWeight() {
    weight_ = random.next(-weight_variance, weight_variance);
}

bool Connection::operator==(const Connection &rhs) const {
    return id == rhs.id &&
            weight_ == rhs.weight_ &&
            input_ == rhs.input_ &&
            output_ == rhs.output_;
}

bool Connection::operator!=(const Connection &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Connection &connection) {
    os << "[No.: " << connection.id << " In " << *connection.input_ << " Out "
       << *connection.output_ << " Weight " << connection.weight_ << "]";
    return os;
}

const PNeuron &Connection::getInput() const {
    return input_;
}

const PNeuron &Connection::getOutput() const {
    return output_;
}

double Connection::getWeight() const {
    return weight_;
}
