file(GLOB TEST_SOURCES
        "*.h"
        "*.cc"
        "*.hpp"
        )

file(GLOB SOURCES
        "${TEST_DIR}/*.h"
        "${TEST_DIR}/*.cc"
        "${TEST_DIR}/*.hpp"
        )

add_executable(GeneTest
        GeneTest.cc
        ${SOURCES}
        ${ARMADILLO_LIBRARIES}
        ${Boost_LIBRARIES})