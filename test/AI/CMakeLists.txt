cmake_minimum_required(VERSION 2.6)

add_executable(NeuralNetworkTest NeuralNetworkTest.cc)
target_link_libraries(NeuralNetworkTest  ${ARMADILLO_LIBRARIES}
                                        ${Boost_LIBRARIES})

add_executable(PhenomeTest PhenomeTest.cc
                             ${TEST_DIR}/Phenome.h
                             ${TEST_DIR}/Phenome.cc
                             ${TEST_DIR}/Genome.h
                             ${TEST_DIR}/Genome.cc
                             ${TEST_DIR}/Genotype.h
                             ${TEST_DIR}/Genotype.cc
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
target_link_libraries(GenomeTest ${ARMADILLO_LIBRARIES}
                                   ${Boost_LIBRARIES})

add_executable(GeneTest GeneTest.cc
        ${TEST_DIR}/Gene.h
        ${TEST_DIR}/Gene.cc
        ${TEST_DIR}/Neuron.h
        ${TEST_DIR}/Neuron.cc
        ${TEST_DIR}/Connection.h
        ${TEST_DIR}/Connection.cc
        ${TEST_DIR}/Random.h
        ${TEST_DIR}/Random.cc)
target_link_libraries(GeneTest         ${ARMADILLO_LIBRARIES}
        ${Boost_LIBRARIES})

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
target_link_libraries(GenotypeTest        ${ARMADILLO_LIBRARIES}
        ${Boost_LIBRARIES})