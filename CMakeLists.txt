cmake_minimum_required(VERSION 3.6)
project(MachineGaming)

set(CMAKE_CXX_STANDARD 11)

find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

if (WIN32)
    set(ARMADILLO_LIBRARIES ${PROJECT_SOURCE_DIR}/lib/libarmadillo.dll)
    set(ARMADILLO_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
else()
    find_package(Armadillo REQUIRED)
endif()
include_directories(${ARMADILLO_INCLUDE_DIRS})

set(Boost_USE_MULTITHREADED      ON)
find_package(Boost COMPONENTS log python unit_test_framework)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})

# Locate classes we want to test
set(TEST_DIR ${MachineGaming_SOURCE_DIR}/src/AI)
include_directories (${TEST_DIR})

add_subdirectory(src)
add_subdirectory(test)