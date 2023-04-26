cmake -B bin -S .
cmake --build bin
#valgrind --track-origins=yes  bin/bubblesort_mini
## reset;cmake --build bin &&
