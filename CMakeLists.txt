cmake_minimum_required(VERSION 3.5.1)
project(MachineGaming)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES_DIR ${MachineGaming_SOURCE_DIR}/src/AI)
set(TEST_DIR ${MachineGaming_SOURCE_DIR}/test/AI)

find_package(PythonLibs 3 REQUIRED)

find_package(Boost COMPONENTS python-py35 unit_test_framework serialization)
add_definitions(-DBOOST_TEST_DYN_LINK)
find_package(Armadillo REQUIRED)

enable_testing()
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${ARMADILLO_INCLUDE_DIRS} ${SOURCES_DIR})
link_libraries(${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${ARMADILLO_LIBRARIES})

add_subdirectory(res)
add_subdirectory(src)
add_subdirectory(test)
