cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Locate classes we want to test
set(TEST_DIR ${MachineGaming_SOURCE_DIR}/src/AI)
include_directories (${TEST_DIR})

set(HEADERS ${TEST_DIR}/NeuralNetwork.h)
set(SOURCES NeuralNetworkTest.cc
            ${TEST_DIR}/NeuralNetwork.cc)

# Link test with what we want to test and the GTest and pthread libs
add_executable(NeuralNetworkTest ${HEADERS} ${SOURCES})
target_link_libraries(NeuralNetworkTest
                      ${GTEST_LIBRARIES}
                      ${ARMADILLO_LIBRARIES}
                      pthread)