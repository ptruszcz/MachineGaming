cmake_minimum_required(VERSION 3.5.1)
project(MachineGaming)

set(CMAKE_CXX_STANDARD 14)

find_package(PythonLibs 3 REQUIRED)

if (WIN32)
    find_package(Boost COMPONENTS python unit_test_framework)
    set(ARMADILLO_LIBRARIES ${PROJECT_SOURCE_DIR}/lib/libarmadillo.dll)
    set(ARMADILLO_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
elseif(UNIX)
    find_package(Boost COMPONENTS python-py35 unit_test_framework)
    add_definitions(-DBOOST_TEST_DYN_LINK)
    find_package(Armadillo REQUIRED)
endif()

enable_testing()
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${ARMADILLO_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${ARMADILLO_LIBRARIES})

set(SOURCES_DIR ${MachineGaming_SOURCE_DIR}/src/AI)
include_directories(${SOURCES_DIR})

add_subdirectory(src)
add_subdirectory(test)
