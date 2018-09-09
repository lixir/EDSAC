cmake_minimum_required(VERSION 3.9)
project(EDSAC)

set(CMAKE_C_STANDARD  11)

add_executable(EDSAC edsac.c main.c edsac.h tests.c)