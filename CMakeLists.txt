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

add_executable(demosort demo_main.c demo_postprocess.c demo_preprocess.c demo_sort.c)
target_compile_options(demosort PRIVATE -Wall -g)

add_executable(demosort_mini demo_sort.c)
target_compile_options(demosort_mini PRIVATE -Wall -g -D ENABLE_LOCAL_MAIN)

add_executable(bubblesort_mini demo_sort.c)
target_compile_options(bubblesort_mini PRIVATE -Wall -O3 -D ENABLE_LOCAL_MAIN)
