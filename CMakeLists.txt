cmake_minimum_required(VERSION 3.4)
project(word_scorer_project)
add_subdirectory(pybind11)
pybind11_add_module(word_scorer main.cpp src/Trie.cpp src/Parser.cpp src/WordScorer.cpp)