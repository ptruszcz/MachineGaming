cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

find_package(Boost REQUIRED log)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})

# Locate classes we want to test
set(TEST_DIR ${MachineGaming_SOURCE_DIR}/src/AI)
include_directories (${TEST_DIR})

# Link test with what we want to test and the GTest and pthread libs
add_executable(NeuralNetworkTest NeuralNetworkTest.cc
                                 ${TEST_DIR}/NeuralNetwork.h
                                 ${TEST_DIR}/NeuralNetwork.cc)
target_link_libraries(NeuralNetworkTest ${GTEST_LIBRARIES}
                                        ${ARMADILLO_LIBRARIES}
                                        ${Boost_LIBRARIES}
                                        pthread)

add_executable(PhenomeTest PhenomeTest.cc
                             ${TEST_DIR}/Phenome.h
                             ${TEST_DIR}/Phenome.cc
                             ${TEST_DIR}/Genome.h
                             ${TEST_DIR}/Genome.cc
                             ${TEST_DIR}/Random.h
                             ${TEST_DIR}/Random.cc
                             ${TEST_DIR}/Gene.h
                             ${TEST_DIR}/Gene.cc
                             ${TEST_DIR}/Neuron.h
                             ${TEST_DIR}/Neuron.cc
                             ${TEST_DIR}/Connection.h
                             ${TEST_DIR}/Connection.cc)
target_link_libraries(PhenomeTest ${GTEST_LIBRARIES}
                                    ${ARMADILLO_LIBRARIES}
                                    ${Boost_LIBRARIES}
                                    pthread)

add_executable(GenomeTest GenomeTest.cc
                            ${TEST_DIR}/Genome.h
                            ${TEST_DIR}/Genome.cc
                            ${TEST_DIR}/Random.h
                            ${TEST_DIR}/Random.cc
                            ${TEST_DIR}/Genotype.h
                            ${TEST_DIR}/Genotype.cc
                            ${TEST_DIR}/Gene.h
                            ${TEST_DIR}/Gene.cc
                            ${TEST_DIR}/Neuron.h
                            ${TEST_DIR}/Neuron.cc
                            ${TEST_DIR}/Connection.h
                            ${TEST_DIR}/Connection.cc)
target_link_libraries(GenomeTest ${GTEST_LIBRARIES}
                                   ${ARMADILLO_LIBRARIES}
                                   ${Boost_LIBRARIES}
                                   pthread)

add_executable(GeneTest GeneTest.cc
        ${TEST_DIR}/Gene.h
        ${TEST_DIR}/Gene.cc
        ${TEST_DIR}/Neuron.h
        ${TEST_DIR}/Neuron.cc
        ${TEST_DIR}/Connection.h
        ${TEST_DIR}/Connection.cc
        ${TEST_DIR}/Random.h
        ${TEST_DIR}/Random.cc)
target_link_libraries(GeneTest ${GTEST_LIBRARIES}
        ${ARMADILLO_LIBRARIES}
        ${Boost_LIBRARIES}
        pthread)

add_executable(GenotypeTest GenotypeTest.cc
        ${TEST_DIR}/Genotype.h
        ${TEST_DIR}/Genotype.cc
        ${TEST_DIR}/Gene.h
        ${TEST_DIR}/Gene.cc
        ${TEST_DIR}/Neuron.h
        ${TEST_DIR}/Neuron.cc
        ${TEST_DIR}/Connection.h
        ${TEST_DIR}/Connection.cc
        ${TEST_DIR}/Random.h
        ${TEST_DIR}/Random.cc)
target_link_libraries(GenotypeTest ${GTEST_LIBRARIES}
        ${ARMADILLO_LIBRARIES}
        ${Boost_LIBRARIES}
        pthread)