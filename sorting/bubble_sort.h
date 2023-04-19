#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

#include <stdlib.h>

void bubble_sort(void *array, size_t array_length, size_t elem_size,
                 __compar_fn_t compare_f);
#endif
