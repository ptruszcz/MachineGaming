set(Boost_USE_MULTITHREADED      ON)

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(Boost 1.45.0 COMPONENTS python)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

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