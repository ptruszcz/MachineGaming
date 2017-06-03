/**
 * @enum MutationType
 * @brief Represents different mutation types.
 * @details This enum is passed in mutate methods.
 * @author Jakub Fajkowski
 */

#ifndef MACHINEGAMING_MUTATIONTYPE_H
#define MACHINEGAMING_MUTATIONTYPE_H

static const int NUM_OF_MUTATION_TYPES = 5;

enum MutationType {
    ADD_NEURON = 0,
    ADD_CONNECTION = 1,
    DELETE_CONNECTION = 2,
    DELETE_NEURON = 3,
    RANDOMIZE_WEIGHT = 4
};

#endif //MACHINEGAMING_MUTATIONTYPE_H
