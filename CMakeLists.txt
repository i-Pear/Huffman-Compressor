cmake_minimum_required(VERSION 3.15)
project(HCompressor)

set(CMAKE_CXX_STANDARD 14)

add_executable(HCompressor main.cpp PriorityQueue.h HuffmanEncoder.h HuffmanDecoder.h HuffmanDecoder.cpp HuffmanEncoder.cpp)