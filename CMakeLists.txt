cmake_minimum_required(VERSION 3.5.1)
project(MachineGaming)

set(CMAKE_CXX_STANDARD 11)

find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

if (WIN32)
    find_package(Boost COMPONENTS python unit_test_framework)
    set(ARMADILLO_LIBRARIES ${PROJECT_SOURCE_DIR}/lib/libarmadillo.dll)
    set(ARMADILLO_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
elseif(UNIX)
    find_package(Boost COMPONENTS python-py35 unit_test_framework)
    ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
    find_package(Armadillo REQUIRED)
endif()

set(Boost_USE_MULTITHREADED      ON)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${ARMADILLO_INCLUDE_DIRS})

# Locate classes we want to test
set(TEST_DIR ${MachineGaming_SOURCE_DIR}/src/AI)
include_directories (${TEST_DIR})

add_subdirectory(src)
add_subdirectory(test)
