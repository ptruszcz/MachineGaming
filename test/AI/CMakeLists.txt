add_executable(CounterTest CounterTest.cc)
target_link_libraries(CounterTest pyvolution)
add_test(NAME CounterTest COMMAND CounterTest)

add_executable(EvolutionaryAlgorithmTest EvolutionaryAlgorithmTest.cc)
target_link_libraries(EvolutionaryAlgorithmTest pyvolution)
add_test(NAME EvolutionaryAlgorithmTest COMMAND EvolutionaryAlgorithmTest)

add_executable(GeneTest GeneTest.cc)
target_link_libraries(GeneTest pyvolution)
add_test(NAME GeneTest COMMAND GeneTest)

add_executable(GenomeTest GenomeTest.cc)
target_link_libraries(GenomeTest pyvolution)
add_test(NAME GenomeTest COMMAND GenomeTest)

add_executable(GenotypeTest GenotypeTest.cc)
target_link_libraries(GenotypeTest pyvolution)
add_test(NAME GenotypeTest COMMAND GenotypeTest)

add_executable(NeuralNetworkTest NeuralNetworkTest.cc)
target_link_libraries(NeuralNetworkTest pyvolution)
add_test(NAME NeuralNetworkTest COMMAND NeuralNetworkTest)

add_executable(PhenomeTest PhenomeTest.cc)
target_link_libraries(PhenomeTest pyvolution)
add_test(NAME PhenomeTest COMMAND PhenomeTest)

add_executable(WrappersTest WrappersTest.cc)
target_link_libraries(WrappersTest pyvolution)
add_test(NAME WrappersTest COMMAND WrappersTest)

file(COPY pyvolutionTest.py DESTINATION .)
add_test(NAME pyvolutionTest COMMAND ${PYTHON_EXECUTABLE} pyvolutionTest.py)