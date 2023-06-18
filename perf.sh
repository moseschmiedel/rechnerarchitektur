#!/bin/bash


run_perf() {
    echo "TIME,measurement_type"
    perf stat -e cpu-clock,cycles,instructions,duration_time -i -x , "${@:1}" 2>&1
    sleep 0.1
    echo "CACHE,measurement_type"
    perf stat -e cpu-clock,cycles,instructions,page-faults,cache-references,cache-misses,branches,branch-misses,duration_time -x , "${@:1}" 2>&1
}

for sobel in $(ls bin/sobel-sequential-*)
do
    echo ""
    echo "$sobel,title"
    echo "sequential,execution_mode"
    run_perf "$sobel"
done

for sobel in $(ls bin/sobel-parallel-*)
do
    for num_threads in 1 2 4 8
    do
        echo ""
        echo "$sobel,title"
        echo "parallel,execution_mode"
        echo "$num_threads,num_threads"
        run_perf "$sobel" "$num_threads"
    done
done
