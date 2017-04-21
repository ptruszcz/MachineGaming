#include "Neuron.h"

Neuron::Neuron(int layer_number) : Counter(), Gene(howMany()) {
    this->layer_number = layer_number;
}

Neuron::Neuron(const Neuron &neuron) : Counter(neuron), Gene(neuron) {
    this->layer_number = neuron.layer_number;
}

PGene Neuron::clone() const {
    return std::make_shared<Neuron>(*this);
}

void Neuron::mutate(MutationType mutation_type) {}

int Neuron::getLayerNumber() const {
    return layer_number;
}

bool Neuron::operator==(const Neuron &rhs) const {
    return id == rhs.id &&
            layer_number == rhs.layer_number;
}

bool Neuron::operator!=(const Neuron &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Neuron &neuron) {
    os << "[No. " << neuron.id << " Layer " << neuron.layer_number << "]";
    return os;
}
