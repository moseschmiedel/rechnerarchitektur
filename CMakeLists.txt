cmake_minimum_required(VERSION 3.19)

project (sortieren NONE)

enable_language(C)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_SYSTEM_NAME Linux)
#set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLI_COMPILE_OPTIONS -Wall -g)

add_executable(std_qsort main.c postprocess.c preprocess.c include/qsort.include.c)
target_compile_options(std_qsort PRIVATE "${CLI_COMPILE_OPTIONS}")

set(SORT_FUNCTION_NAME "bubble_sort")
add_executable(bubble_sort main.c postprocess.c preprocess.c include/bubble_sort.include.c)
target_compile_options(bubble_sort PRIVATE "${CLI_COMPILE_OPTIONS}")

set(SORT_FUNCTION_NAME "insertion_sort")
add_executable(insertion_sort main.c postprocess.c preprocess.c include/insertion_sort.include.c)
target_compile_options(insertion_sort PRIVATE "${CLI_COMPILE_OPTIONS}")

set(SORT_FUNCTION_NAME "quick_sort")
add_executable(quick_sort main.c postprocess.c preprocess.c include/quick_sort.include.c)
target_compile_options(quick_sort PRIVATE "${CLI_COMPILE_OPTIONS}")
