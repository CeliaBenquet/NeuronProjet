
cmake_minimum_required (VERSION 2.6)

project (Neuron)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(gtest)
include_directories(gtest/include gtest)

add_executable (Neuron main.cpp Neuron.cpp Network.cpp)
add_executable (Neuron_test mainTest.cpp Neuron.cpp Network.cpp)

target_link_libraries(Neuron_test gtest gtest_main)
add_test(Neuron_test Neuron_test)
