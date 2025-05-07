cmake_minimum_required(VERSION 3.15...3.22)
project(listPy LANGUAGES CXX)

find_package(Python 3.13 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)


pybind11_add_module(listPy listPy.cpp)