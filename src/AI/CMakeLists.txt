file(GLOB SOURCES
        "*.h"
        "*.cc"
        "*.hpp"
        )

# Build our library
add_library(EvolutionaryNeuralNetwork SHARED ${SOURCES})

# Define the wrapper library that wraps our library
add_library(EvolutionaryNeuralNetwork_Ext SHARED evolutionaryalgorithm_ext.cc neuralnetwork_ext.cc
        ${PYTHON_LIBRARIES}
        ${Boost_LIBRARIES})

target_link_libraries(EvolutionaryNeuralNetwork_Ext ${Boost_LIBRARIES} EvolutionaryNeuralNetwork)
# don't prepend wrapper library name with lib
set_target_properties(EvolutionaryNeuralNetwork_Ext PROPERTIES PREFIX "")