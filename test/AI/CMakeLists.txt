file(GLOB SOURCES
        "${SOURCES_DIR}/*.h"
        "${SOURCES_DIR}/*.cc"
        "${SOURCES_DIR}/*.hpp"
        )

add_executable(CounterTest CounterTest.cc ${SOURCES})
add_test(NAME CounterTest COMMAND CounterTest)

add_executable(EvolutionaryAlgorithmTest EvolutionaryAlgorithmTest.cc ${SOURCES})
add_test(NAME EvolutionaryAlgorithmTest COMMAND EvolutionaryAlgorithmTest)

add_executable(GeneTest GeneTest.cc ${SOURCES})
add_test(NAME GeneTest COMMAND GeneTest)

add_executable(GenomeTest GenomeTest.cc ${SOURCES})
add_test(NAME GenomeTest COMMAND GenomeTest)

add_executable(GenotypeTest GenotypeTest.cc ${SOURCES})
add_test(NAME GenotypeTest COMMAND GenotypeTest)

add_executable(NeuralNetworkTest NeuralNetworkTest.cc ${SOURCES})
add_test(NAME NeuralNetworkTest COMMAND NeuralNetworkTest)

add_executable(PhenomeTest PhenomeTest.cc ${SOURCES})
add_test(NAME PhenomeTest COMMAND PhenomeTest)

add_executable(WrappersTest WrappersTest.cc ${SOURCES})
add_test(NAME WrappersTest COMMAND WrappersTest)

file(COPY pyvolutionTest.py DESTINATION .)
add_test(NAME pyvolutionTest COMMAND ${PYTHON_EXECUTABLE} pyvolutionTest.py)