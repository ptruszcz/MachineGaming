cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Locate classes we want to test
set(TEST_DIR ${MachineGaming_SOURCE_DIR}/src/AI)
include_directories (${TEST_DIR})

# Link test with what we want to test and the GTest and pthread libs
add_executable(NeuralNetworkTest NeuralNetworkTest.cc
                                 ${TEST_DIR}/NeuralNetwork.h
                                 ${TEST_DIR}/NeuralNetwork.cc)
target_link_libraries(NeuralNetworkTest ${GTEST_LIBRARIES}
                                        ${ARMADILLO_LIBRARIES}
                                        pthread)

add_executable(PhenotypeTest PhenotypeTest.cc
                             ${TEST_DIR}/Phenotype.h
                             ${TEST_DIR}/Phenotype.cc
                             ${TEST_DIR}/Genotype.h
                             ${TEST_DIR}/Genotype.cc)
target_link_libraries(PhenotypeTest ${GTEST_LIBRARIES}
                                    ${ARMADILLO_LIBRARIES}
                                    pthread)

add_executable(GenotypeTest GenotypeTest.cc
                            ${TEST_DIR}/Genotype.h
                            ${TEST_DIR}/Genotype.cc
                            ${TEST_DIR}/Random.h
                            ${TEST_DIR}/Random.cc
                            ${TEST_DIR}/Neuron.h
                            ${TEST_DIR}/Neuron.cc
                            ${TEST_DIR}/Connection.h
                            ${TEST_DIR}/Connection.cc)
target_link_libraries(GenotypeTest ${GTEST_LIBRARIES}
        ${ARMADILLO_LIBRARIES}
        pthread)