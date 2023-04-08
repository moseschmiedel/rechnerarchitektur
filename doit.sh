cmake -B bin -S .
cmake --build bin
## reset;cmake --build bin && valgrind --track-origins=yes  bin/demo