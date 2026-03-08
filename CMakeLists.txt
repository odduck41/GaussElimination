cmake_minimum_required(VERSION 4.0)
project(GaussElimination C)

set(CMAKE_C_STANDARD 23)

add_executable(GaussElimination
        main.c
        matrix/matrix.c
        matrix/calc/DetCalculation.c
        legacy/Test.c
)
