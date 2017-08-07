cmake_minimum_required(VERSION 2.6)
project(pepeui)

add_executable(pepeui main.cpp)

install(TARGETS pepeui RUNTIME DESTINATION bin)
