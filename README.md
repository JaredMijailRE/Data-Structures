

# Data Structures Implementation and Performance Analysis

This repository implements various data structures in Python, C++, and Zig, including Trees, Lists, Linked Lists, Union-Find, and Hash Tables. It analyzes the complexity of these data structures and compares their performance across different implementations.

## Features

* Implementations of fundamental data structures:

  * Trees (AVL, BST, HEAP)
  * Lists
  * Linked Lists (Single, Double, Tail)
  * Union-Find
  * Hash Tables
* Complexity analysis of each data structure.
* Performance comparisons between different implementations.
* Integration of C++ and Zig code into Python using Pybind11.
* Compilation of code with CMake.
* Analysis conducted using Jupyter Notebooks.

## Repository Structure

* `Src/`: Source code for data structure implementations.
* `structures/`: Compile code to run in the notebooks.
* `Exercise/`: Exercises solved using the implemented data structures.
* `analisysHash.ipynb`: Jupyter Notebook analyzing hash table implementations.
* `analisysList.ipynb`, `analisysList2.ipynb`, `analisysList3.ipynb`: Jupyter Notebooks analyzing the rest of the structures.

## Notes

* The project utilizes Pybind11 to integrate C++ and Zig code into Python, allowing for seamless performance comparisons.
* All analyses are conducted within Jupyter Notebooks, providing an interactive environment for exploration.
* The implementations are executed through the CPython interpreter.

## License

This project is licensed under the MIT License.
