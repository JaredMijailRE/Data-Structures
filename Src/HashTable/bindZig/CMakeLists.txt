cmake_minimum_required(VERSION 3.15...3.22)
project(HashTable LANGUAGES CXX)

find_package(Python 3.13 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Assume your source files (wrapper.cpp, HashTable.h, and HashTable.zig) are in the current directory.
set(ZIG_SOURCE "${CMAKE_SOURCE_DIR}/HashTable.zig")
set(ZIG_LIB "${CMAKE_SOURCE_DIR}/libHashTable.so")
set(ZIG_HEADER "${CMAKE_SOURCE_DIR}/HashTable.h")

# Add a custom target to build the Zig library.
add_custom_target(ZigHashTableLib ALL
    COMMAND zig build-lib ${ZIG_SOURCE} -dynamic -femit-h=${ZIG_HEADER} -fPIC
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building Zig HashTable library..."
)

pybind11_add_module(HashTable wrapper.cpp)

add_dependencies(HashTable ZigHashTableLib)

target_link_libraries(HashTable PRIVATE ${ZIG_LIB})

include_directories(${CMAKE_SOURCE_DIR})
