#include <string.h>

#include "insertion_sort.h"

/* **************************************************
 * Public function
 * ************************************************** */

void insertion_sort(void *array, size_t array_length, size_t elem_size,
                    __compar_fn_t compare_f) {
    char *array_base = (char *)array;

    for (size_t sort_idx = 1; sort_idx < array_length; ++sort_idx) {
        char *elem1 = &array_base[elem_size * sort_idx];
        size_t insertion_idx = sort_idx;
        while (insertion_idx &&
               compare_f(elem1, &array_base[elem_size * insertion_idx]) < 1) {
            --insertion_idx;
        }

        if (insertion_idx != sort_idx) {
            char temp[elem_size];
            memcpy(temp, elem1, elem_size);
            memmove(&array_base[elem_size * (insertion_idx + 1)],
                    &array_base[elem_size * insertion_idx],
                    elem_size * (sort_idx - insertion_idx));
            memcpy(&array_base[elem_size * insertion_idx], temp, elem_size);
        }
    }
}
