cmake_minimum_required(VERSION 3.13)
project(tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(tree main.cpp min_heap.cpp min_heap.h b_tree.cpp b_tree.h top_k_frequent_word.cpp top_k_frequent_word.h find_elements_equelse_to_sum.cpp find_elements_equelse_to_sum.h)