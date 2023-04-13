#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

struct range {
    char *low;
    char *high;
};

#define PUSH(lo, hi) ((void)((top->low = (lo)), (top->high = (hi)), ++top))
#define POP(lo, hi) ((void)(--top, (lo = top->low), (hi = top->high)))
#define STACK_EMPTY ((top - base) <= 0)

/* **************************************************
 * Public function
 * ************************************************** */

void quick_sort(void *array, size_t array_length, size_t elem_size,
                __compar_fn_t compare_f) {
    if (array_length <= 1)
        return;

    char *array_base = (char *)array;

    // stack initializiation
    struct range base[array_length];
    struct range *top = &base[0];

    char *pivot;
    char *i, *j, *mid;
    char *lo = array_base;
    char *hi = array_base + elem_size * (array_length - 1);

    char temp[elem_size];

    bool sorting = true;
    bool scanning = true;

    while (sorting) {
        if (hi - lo <= elem_size) {
            if (compare_f(lo, hi) > 0) {
                memcpy(temp, lo, elem_size);
                memmove(lo, hi, elem_size);
                memcpy(hi, temp, elem_size);
            }
            j = lo;
            i = hi;
        } else {

            // Median-of-Three pivot choice
            // A[l + 1] :=: A[(l + r) / 2]
            mid = lo + ((hi - lo) / elem_size >> 1) * elem_size;
            memcpy(temp, mid, elem_size);
            memmove(mid, lo + elem_size, elem_size);
            memcpy(lo + elem_size, temp, elem_size);

            // if A[l + 1] > A[r] then A [l + 1] :=: A[r] endif;
            if (compare_f(lo + elem_size, hi) > 0) {
                memcpy(temp, lo + elem_size, elem_size);
                memmove(lo + elem_size, hi, elem_size);
                memcpy(hi, temp, elem_size);
            }
            // if A[l] > A[r] then A[l] :=: A[r] endif;
            if (compare_f(lo, hi) > 0) {
                memcpy(temp, lo, elem_size);
                memmove(lo, hi, elem_size);
                memcpy(hi, temp, elem_size);
            }
            // if A[l + 1] > A[1] then A[l + 1] :=: A[l] endif;
            if (compare_f(lo + elem_size, lo) > 0) {
                memcpy(temp, lo + elem_size, elem_size);
                memcpy(lo + elem_size, lo, elem_size);
                memcpy(lo, temp, elem_size);
            }

            pivot = lo;
            i = lo;
            j = hi + elem_size;

            // Partition
            scanning = true;
            while (scanning) {
                do {
                    i += elem_size;
                } while (i < hi && compare_f(i, pivot) < 0);
                do {
                    j -= elem_size;
                } while (compare_f(j, pivot) > 0);

                if (j >= i) {
                    memcpy(temp, i, elem_size);
                    memmove(i, j, elem_size);
                    memcpy(j, temp, elem_size);
                } else {
                    scanning = false;
                }
            };
            memcpy(temp, j, elem_size);
            memmove(j, pivot, elem_size);
            memcpy(pivot, temp, elem_size);
        }

        // Stop case and Stack manipulation
        if (MAX(j - lo, hi - i + elem_size) <= elem_size) {
            if (STACK_EMPTY) {
                sorting = false;
            } else {
                POP(lo, hi);
            }
        } else if (MIN(j - lo, hi - i + elem_size) <= elem_size) {
            if (j - lo > hi - i + elem_size) {
                hi = j - elem_size;
            } else {
                lo = i;
            }
        } else {
            if (j - lo > hi - i + elem_size) {

                PUSH(lo, (j - elem_size));
                lo = i;
            } else {
                PUSH(i, hi);
                hi = j - elem_size;
            }
        }
    }
}
