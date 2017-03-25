//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_CONNECTION_H
#define MACHINEGAMING_CONNECTION_H


#include <boost/shared_ptr.hpp>
#include "Neuron.h"

class Connection {
private:
    static int counter;
    int order_number;
    boost::shared_ptr<Neuron> input;
    boost::shared_ptr<Neuron> output;
    double weight;

public:
    double weight_variance;
    bool enabled;

    Connection(const boost::shared_ptr<Neuron> &input, const boost::shared_ptr<Neuron> &output);

    void randomizeWeight();

    int getOrderNumber() const;
    const boost::shared_ptr<Neuron> &getInput() const;
    const boost::shared_ptr<Neuron> &getOutput() const;
    bool isEnabled() const;
    double getWeight() const;
};


#endif //MACHINEGAMING_CONNECTION_H
