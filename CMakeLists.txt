cmake_minimum_required(VERSION 3.13)
project(assign2 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -lm)

add_executable(ku_purisai ku_purisai.c ku_purisai.h)
add_executable(ku_turisai ku_turisai.c ku_turisai.h)