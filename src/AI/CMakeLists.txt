file(GLOB SOURCES
        "*.h"
        "*.cc"
        "*.hpp"
        )

# Build our library
add_library(NeuralNetwork SHARED ${SOURCES})

target_link_libraries(NeuralNetwork
        ${ARMADILLO_LIBRARIES}
        ${Boost_LIBRARIES})

# Define the wrapper library that wraps our library
add_library(NeuralNetwork_Ext SHARED neuralnetwork_ext.cc
        ${PYTHON_LIBRARIES}
        ${Boost_LIBRARIES})

target_link_libraries(NeuralNetwork_Ext
                      NeuralNetwork)
# don't prepend wrapper library name with lib
set_target_properties(NeuralNetwork_Ext PROPERTIES PREFIX "")