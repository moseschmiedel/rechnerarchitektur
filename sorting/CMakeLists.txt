cmake_minimum_required(VERSION 3.19)

project (sorting NONE)

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

get_filename_component(PARENT_DIR ../ ABSOLUTE)

foreach(ALGORITHM ${ALGORITHMS})
    cat(${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c.in ${PARENT_DIR}/types.h ${CMAKE_SOURCE_DIR}/sorting.c.in)

    if(EXISTS ${CMAKE_SOURCE_DIR}/${ALGORITHM}.c)
        cat(${CMAKE_BINARY_DIR}/${ALGORITHM}.ripes.c.in ${PARENT_DIR}/types.h ${CMAKE_SOURCE_DIR}/${ALGORITHM}.c ${CMAKE_SOURCE_DIR}/sorting.c.in)
    else()
        cat(${CMAKE_BINARY_DIR}/${ALGORITHM}.ripes.c.in ${PARENT_DIR}/types.h ${CMAKE_SOURCE_DIR}/sorting.c.in)
    endif()

    set(SORT_FUNCTION_NAME ${ALGORITHM})
    if(EXISTS ${CMAKE_SOURCE_DIR}/${ALGORITHM}.c)
        set(INCLUDE_ALGORITHM_HEADER 1)
    endif()
    configure_file(${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c.in ${ALGORITHM}.skeleton.c)

    set(ENABLE_LOCAL_MAIN 1)
    configure_file(${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c.in ${ALGORITHM}.skeleton_mini.c)
    unset(INCLUDE_ALGORITHM_HEADER)
    configure_file(${CMAKE_BINARY_DIR}/${ALGORITHM}.ripes.c.in ${ALGORITHM}.ripes.c)



    foreach(OPTIMIZATION ${OPTIMIZATIONS})
        if(EXISTS ${CMAKE_SOURCE_DIR}/${ALGORITHM}.c)
            add_library(${ALGORITHM}_${OPTIMIZATION} OBJECT ${CMAKE_SOURCE_DIR}/${ALGORITHM}.c)
            target_compile_options(${ALGORITHM}_${OPTIMIZATION} PRIVATE "-${OPTIMIZATION}")

            add_executable(${ALGORITHM}_${OPTIMIZATION}_mini ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton_mini.c)
            target_compile_options(${ALGORITHM}_${OPTIMIZATION}_mini PRIVATE "-g")
            target_link_libraries(${ALGORITHM}_${OPTIMIZATION}_mini PUBLIC ${ALGORITHM}_${OPTIMIZATION})
            target_include_directories(${ALGORITHM}_${OPTIMIZATION}_mini PUBLIC
                "${CMAKE_SOURCE_DIR}"
                )
        else()
            add_executable(${ALGORITHM}_${OPTIMIZATION}_mini ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c)
            target_compile_options(${ALGORITHM}_${OPTIMIZATION}_mini PRIVATE "-g")
        endif()
    endforeach()

    function(${ALGORITHM}_clean)
    endfunction()

    set(OPTIMIZATION_TARGETS ${OPTIMIZATIONS})
    list(TRANSFORM OPTIMIZATION_TARGETS PREPEND ${ALGORITHM}_)
    list(TRANSFORM OPTIMIZATION_TARGETS APPEND _mini)

    add_custom_target(${ALGORITHM}_clean
        COMMAND rm ${CMAKE_BINARY_DIR}/${ALGORITHM}.ripes.c.in
        COMMAND rm ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c.in
        COMMAND rm ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton.c
        COMMAND rm ${CMAKE_BINARY_DIR}/${ALGORITHM}.skeleton_mini.c
    VERBATIM)
    foreach(OPTIMIZATION_TARGET ${OPTIMIZATION_TARGETS})
        add_dependencies(${ALGORITHM}_clean ${OPTIMIZATION_TARGET})
    endforeach()
endforeach()
