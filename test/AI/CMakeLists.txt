file(GLOB TEST_SOURCES
        "*.h"
        "*.cc"
        "*.hpp"
        )

file(GLOB SOURCES
        "${SOURCES_DIR}/*.h"
        "${SOURCES_DIR}/*.cc"
        "${SOURCES_DIR}/*.hpp"
        )

add_executable(AITests ${TEST_SOURCES} ${SOURCES})
add_test(AITests AITests)

add_executable(CounterTest CounterTest.cc ${SOURCES})
add_test(NAME CounterTest COMMAND CounterTest)

file(COPY pyvolutionTest.py DESTINATION .)
add_test(NAME pyvolutionTest COMMAND ${PYTHON_EXECUTABLE} pyvolutionTest.py)