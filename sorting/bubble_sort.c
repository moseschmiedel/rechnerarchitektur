#include <string.h>

#include "bubble_sort.h"

/* **************************************************
 * Public function
 * ************************************************** */

void bubble_sort(void *array, size_t array_length, size_t elem_size,
                 __compar_fn_t compare_f) {
    char *array_base = (char *)array;

    size_t idx = 0;
    size_t swaps = 0;
    do {
        char *elem1 = &array_base[elem_size * idx];
        char *elem2 = &array_base[elem_size * (idx + 1)];
        if (compare_f(elem1, elem2) > 0) {
            char temp[elem_size];
            memcpy(temp, elem1, elem_size);
            memcpy(elem1, elem2, elem_size);
            memcpy(elem2, temp, elem_size);
            ++swaps;
        }
        if (swaps > 0 || (idx + 1) >= array_length) {
            idx = 0;
            swaps = 0;
        } else {
            ++idx;
        }
    } while (!(swaps == 0 && (idx + 1) >= array_length));
}
