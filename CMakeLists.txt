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

set(CLI_COMPILE_OPTIONS -Wall)

# list of all algorithms that should be compiled
set(ALGORITHMS bubble_sort insertion_sort quick_sort qsort)
set(OPTIMIZATIONS g O1 O2 O3)

function(cat OUT_FILE)
    file(WRITE ${OUT_FILE} "")
    foreach(FILE ${ARGV})
        file(READ ${FILE} CONTENTS)
        file(APPEND ${OUT_FILE} "${CONTENTS}")
    endforeach()
endfunction()


foreach(ALGORITHM ${ALGORITHMS})
    cat(${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c.in ${CMAKE_SOURCE_DIR}/types.h ${CMAKE_SOURCE_DIR}/sorting/sorting.c.in)

    if(EXISTS ${CMAKE_SOURCE_DIR}/sorting/${ALGORITHM}.c)
        cat(${CMAKE_BINARY_DIR}/${ALGORITHM}.ripes.c.in ${CMAKE_SOURCE_DIR}/types.h ${CMAKE_SOURCE_DIR}/sorting/${ALGORITHM}.c ${CMAKE_SOURCE_DIR}/sorting/sorting.c.in)
    else()
        cat(${CMAKE_BINARY_DIR}/${ALGORITHM}.ripes.c.in ${CMAKE_SOURCE_DIR}/types.h ${CMAKE_SOURCE_DIR}/sorting/sorting.c.in)
    endif()

    set(SORT_FUNCTION_NAME ${ALGORITHM})
    if(EXISTS ${CMAKE_SOURCE_DIR}/sorting/${ALGORITHM}.c)
        set(INCLUDE_ALGORITHM_HEADER 1)
    endif()
    configure_file(${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c.in ${ALGORITHM}.skeleton.c)

    set(ENABLE_LOCAL_MAIN 1)
    configure_file(${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c.in ${ALGORITHM}.skeleton_mini.c)
    set(INCLUDE_ALGORITHM_HEADER 0)
    set(RIPES 1)
    configure_file(${CMAKE_BINARY_DIR}/${ALGORITHM}.ripes.c.in ${ALGORITHM}.ripes.c)



    foreach(OPTIMIZATION ${OPTIMIZATIONS})
        if(EXISTS ${CMAKE_SOURCE_DIR}/sorting/${ALGORITHM}.c)
            add_library(${ALGORITHM}_${OPTIMIZATION} STATIC ${CMAKE_SOURCE_DIR}/sorting/${ALGORITHM}.c)
            set_target_properties(${ALGORITHM}_${OPTIMIZATION} PROPERTIES PREFIX "lib_")
            set_target_properties(${ALGORITHM}_${OPTIMIZATION} PROPERTIES OUTPUT_NAME ${ALGORITHM})
            set_target_properties(${ALGORITHM}_${OPTIMIZATION} PROPERTIES SUFFIX ".${OPTIMIZATION}.so")
            target_compile_options(${ALGORITHM}_${OPTIMIZATION} PRIVATE ${CLI_COMPILE_OPTIONS} "-${OPTIMIZATION}")

            add_executable(${ALGORITHM}_${OPTIMIZATION}_mini ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton_mini.c)
            target_compile_options(${ALGORITHM}_${OPTIMIZATION}_mini PRIVATE ${CLI_COMPILE_OPTIONS} "-g")
            target_link_libraries(${ALGORITHM}_${OPTIMIZATION}_mini PUBLIC ${ALGORITHM}_${OPTIMIZATION})
            target_include_directories(${ALGORITHM}_${OPTIMIZATION}_mini PUBLIC
                "${CMAKE_SOURCE_DIR}"
                "${CMAKE_SOURCE_DIR}/sorting"
                )
        else()
            add_executable(${ALGORITHM}_${OPTIMIZATION}_mini ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c)
            target_compile_options(${ALGORITHM}_${OPTIMIZATION}_mini PRIVATE ${CLI_COMPILE_OPTIONS} "-g")
        endif()
    endforeach()

    function(${ALGORITHM}_clean)
    endfunction()

    set(OPTIMIZATION_TARGETS ${OPTIMIZATIONS})
    list(TRANSFORM OPTIMIZATION_TARGETS PREPEND ${ALGORITHM}_)
    list(TRANSFORM OPTIMIZATION_TARGETS APPEND _mini)

    add_custom_target(${ALGORITHM}_clean ALL
        COMMAND rm ${CMAKE_BINARY_DIR}/${ALGORITHM}.ripes.c.in
        COMMAND rm ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c.in
        COMMAND rm ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c
        COMMAND rm ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton_mini.c
    VERBATIM)
    foreach(OPTIMIZATION_TARGET ${OPTIMIZATION_TARGETS})
        add_dependencies(${ALGORITHM}_clean ${OPTIMIZATION_TARGET})
    endforeach()
endforeach()

add_executable(sobel-debug sobel.c)
target_link_libraries(sobel-debug PUBLIC m)
target_compile_options(sobel-debug PRIVATE -DENABLE_LOCAL_MAIN -DDEBUG -g)

add_executable(sobel-g sobel.c)
target_link_libraries(sobel-g PUBLIC m)
target_compile_options(sobel-g PRIVATE -DENABLE_LOCAL_MAIN -g)
add_executable(sobel-O1 sobel.c)
target_link_libraries(sobel-O1 PUBLIC m)
target_compile_options(sobel-O1 PRIVATE -DENABLE_LOCAL_MAIN -O1)
add_executable(sobel-O2 sobel.c)
target_link_libraries(sobel-O2 PUBLIC m)
target_compile_options(sobel-O2 PRIVATE -DENABLE_LOCAL_MAIN -O2)
add_executable(sobel-O3 sobel.c)
target_link_libraries(sobel-O3 PUBLIC m)
target_compile_options(sobel-O3 PRIVATE -DENABLE_LOCAL_MAIN -O3)


find_package(OpenMP)
add_executable(sobel-parallel-debug sobel-parallel.c)
target_link_libraries(sobel-parallel-debug PUBLIC m)
target_compile_options(sobel-parallel-debug PRIVATE -DENABLE_LOCAL_MAIN -DDEBUG -g)
if(OpenMP_C_FOUND)
    target_link_libraries(sobel-parallel-debug PUBLIC OpenMP::OpenMP_C)
endif()

add_executable(sobel-parallel-g sobel-parallel.c)
target_link_libraries(sobel-parallel-g PUBLIC m)
target_compile_options(sobel-parallel-g PRIVATE -DENABLE_LOCAL_MAIN -g)
if(OpenMP_C_FOUND)
    target_link_libraries(sobel-parallel-g PUBLIC OpenMP::OpenMP_C)
endif()
add_executable(sobel-parallel-O1 sobel-parallel.c)
target_link_libraries(sobel-parallel-O1 PUBLIC m)
target_compile_options(sobel-parallel-O1 PRIVATE -DENABLE_LOCAL_MAIN -O1)
if(OpenMP_C_FOUND)
    target_link_libraries(sobel-parallel-O1 PUBLIC OpenMP::OpenMP_C)
endif()
add_executable(sobel-parallel-O2 sobel-parallel.c)
target_link_libraries(sobel-parallel-O2 PUBLIC m)
target_compile_options(sobel-parallel-O2 PRIVATE -DENABLE_LOCAL_MAIN -O2)
if(OpenMP_C_FOUND)
    target_link_libraries(sobel-parallel-O2 PUBLIC OpenMP::OpenMP_C)
endif()
add_executable(sobel-parallel-O3 sobel-parallel.c)
target_link_libraries(sobel-parallel-O3 PUBLIC m)
target_compile_options(sobel-parallel-O3 PRIVATE -DENABLE_LOCAL_MAIN -O3)
if(OpenMP_C_FOUND)
    target_link_libraries(sobel-parallel-O3 PUBLIC OpenMP::OpenMP_C)
endif()

# add_executable(std_qsort main.c postprocess.c preprocess.c include/qsort.include.c)
# target_compile_options(std_qsort PRIVATE "${CLI_COMPILE_OPTIONS}")
#
# set(SORT_FUNCTION_NAME "bubble_sort")
# add_executable(bubble_sort main.c postprocess.c preprocess.c include/bubble_sort.include.c)
# target_compile_options(bubble_sort PRIVATE "${CLI_COMPILE_OPTIONS}")
#
# set(SORT_FUNCTION_NAME "insertion_sort")
# add_executable(insertion_sort main.c postprocess.c preprocess.c include/insertion_sort.include.c)
# target_compile_options(insertion_sort PRIVATE "${CLI_COMPILE_OPTIONS}")
#
# set(SORT_FUNCTION_NAME "quick_sort")
# add_executable(quick_sort main.c postprocess.c preprocess.c include/quick_sort.include.c)
# target_compile_options(quick_sort PRIVATE "${CLI_COMPILE_OPTIONS}")
