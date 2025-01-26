cmake_minimum_required(VERSION 3.0.0)
project(learn_c VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

add_compile_options(-Werror -Wall -Wpedantic)

add_executable(funcs src/random_functions.c)
add_executable(calc src/RPNCalc.c)
add_executable(sudoku src/sudoku_solver.c)
target_link_libraries(funcs m)
target_link_libraries(calc m)
target_link_libraries(sudoku m)
