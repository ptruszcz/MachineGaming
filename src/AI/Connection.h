//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_CONNECTION_H
#define MACHINEGAMING_CONNECTION_H

#include <boost/shared_ptr.hpp>
#include "Neuron.h"

class Connection {
private:
    static int connection_counter;
    static double weight_variance;
    int order_number;
    std::shared_ptr<Neuron> input;
    std::shared_ptr<Neuron> output;
    double weight;

public:
    bool enabled;

    Connection(const std::shared_ptr<Neuron> &input, const std::shared_ptr<Neuron> &output);

    void randomizeWeight();

    int getOrderNumber() const;
    const std::shared_ptr<Neuron> &getInput() const;
    const std::shared_ptr<Neuron> &getOutput() const;
    bool isEnabled() const;
    double getWeight() const;

    bool operator==(const Connection &rhs) const;

    bool operator!=(const Connection &rhs) const;
};


#endif //MACHINEGAMING_CONNECTION_H
