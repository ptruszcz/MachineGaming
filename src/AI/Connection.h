/*
File created by: Jakub Fajkowski
*/

#ifndef MACHINEGAMING_CONNECTION_H
#define MACHINEGAMING_CONNECTION_H

#include <ostream>
#include "Neuron.h"
#include "Random.h"
#include "Gene.h"
#include "Counter.hpp"

class Connection;
typedef std::shared_ptr<Connection> PConnection;
typedef std::vector<PConnection> Connections;

class Connection : public Counter<Connection>, public Gene {
private:
    static Random random;

    PNeuron input_;
    PNeuron output_;
    double weight_;
    
    void randomizeWeight();
public:
    static double weight_variance;

    Connection() : Counter(), Gene(howMany()) {};
    Connection(const PNeuron &input, const PNeuron &output);
    Connection(const Connection &connection);
    
    virtual PGene clone() const;
    virtual void mutate(MutationType mutation_type);

    bool operator==(const Connection &rhs) const;
    bool operator!=(const Connection &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Connection &connection);

    const PNeuron &getInput() const;
    const PNeuron &getOutput() const;
    double getWeight() const;
};


#endif //MACHINEGAMING_CONNECTION_H
