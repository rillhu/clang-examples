cmake_minimum_required(VERSION 3.10)
project(graph C)

set(CMAKE_C_STANDARD 99)

add_executable(graph main.c graph_struct.c graph_struct.h)