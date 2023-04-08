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

add_executable(bubblesort demo_main.c demo_postprocess.c demo_preprocess.c bubble_sort.c)
target_compile_options(bubblesort PRIVATE -Wall -g)

add_executable(bubblesort_mini bubble_sort.c)
target_compile_options(bubblesort_mini PRIVATE -Wall -g -D ENABLE_LOCAL_MAIN)

add_executable(insertionsort demo_main.c demo_postprocess.c demo_preprocess.c insertion_sort.c)
target_compile_options(insertionsort PRIVATE -Wall -g)

add_executable(insertionsort_mini insertion_sort.c)
target_compile_options(insertionsort_mini PRIVATE -Wall -g -D ENABLE_LOCAL_MAIN)

add_executable(quicksort demo_main.c demo_postprocess.c demo_preprocess.c quick_sort.c)
target_compile_options(quicksort PRIVATE -Wall -g)

add_executable(quicksort_mini quick_sort.c)
target_compile_options(quicksort_mini PRIVATE -Wall -g -D ENABLE_LOCAL_MAIN)
