
cmake_minimum_required (VERSION 2.6)

project (Neuron)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11 -g")

enable_testing()
add_subdirectory(gtest)
include_directories(gtest/include gtest)

add_executable (Neuron main.cpp Neuron.cpp Network.cpp Simulation.cpp)
add_executable (Neuron_test mainTest.cpp Neuron.cpp Network.cpp Simulation.cpp)

target_link_libraries(Neuron_test gtest gtest_main)
add_test(Neuron_test Neuron_test)

find_package(Doxygen)
if(DOXYGEN_FOUND)
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in) 
message (FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
- ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found.
- Generate one in the project folder with doxygen -g Doxyfile.in")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile@ONLY)
add_custom_target(doc 
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.in 		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
ELSE(DOXYGEN_FOUND)
message (FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)
