file(GLOB SOURCES
        "*.h"
        "*.cc"
        "*.hpp"
        )

# Define the wrapper library that wraps our library
add_library(EvolutionaryNeuralNetwork_Ext SHARED neuralnetwork_ext.cc evolutionaryalgorithm_ext.cc
        ${PYTHON_LIBRARIES}
        ${Boost_LIBRARIES})

target_link_libraries(EvolutionaryNeuralNetwork_Ext)
# don't prepend wrapper library name with lib
set_target_properties(EvolutionaryNeuralNetwork_Ext PROPERTIES PREFIX "")