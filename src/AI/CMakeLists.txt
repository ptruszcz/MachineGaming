# Build our library
add_library(NeuralNetwork SHARED NeuralNetwork.cc)

# Define the wrapper library that wraps our library
add_library(NeuralNetwork_Ext SHARED neuralnetwork_ext.cc)

target_link_libraries(NeuralNetwork_Ext
                      ${ARMADILLO_LIBRARIES}
                      ${PYTHON_LIBRARIES}
                      ${Boost_LIBRARIES}
                      NeuralNetwork)
# don't prepend wrapper library name with lib
set_target_properties( NeuralNetwork_Ext PROPERTIES PREFIX "" )