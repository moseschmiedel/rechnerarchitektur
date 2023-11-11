#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct handle_struct {
    int argc;
    char **argv;

    uint32_t KVPs;
    uint8_t verbose;
    uint8_t data_variant;
    uint64_t nanoseconds; // timediff
};

int pre_process(int argc, char **argv, struct handle_struct *h);
int post_process(struct handle_struct *h);
int sort_handle_struct(struct handle_struct *h);
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ASC 0
#define DESC 1
#define VAR1 2
#define VAR2 3

// clang-format off
#define SORT_FUNCTION_NAME quick_sort
#define ENABLE_LOCAL_MAIN 1
/* #undef INCLUDE_ALGORITHM_HEADER */
#define RIPES 1
// clang-format on

#ifdef INCLUDE_ALGORITHM_HEADER
#include "quick_sort.h"
#endif

#ifndef SORT_FUNCTION_NAME
#define SORT_FUNCTION_NAME qsort
#endif

/* struct holds the array to sort/sorted */
struct mysort_data_struct {
    uint32_t len;    // the number of elements in array
    void **array;    // sortable pointers to the origin array
    void *_internal; // points to the origin array
};

/* defines the struct of one element in the array to sort */
struct mysort_simple_2uint_struct {
    uint64_t key;
    uint64_t value;
};

#ifdef ENABLE_LOCAL_MAIN
int main(int argc, char **argv) {
    struct handle_struct h;
    h.argc = argc;
    h.argv = argv;
    /* Defaults */
    h.KVPs = 32;
    h.verbose = 0;
    h.data_variant = 0;
    h.nanoseconds = 0;
    if (1 < argc)
        h.verbose = 1;
    return sort_handle_struct(&h);
}
#endif

/**
 * allocated memory must be freed after usage
 * call __free_demo() to clean up
 * ***********************************************************/
int __free_demo(struct mysort_data_struct *data) {
    if (NULL == data)
        return 0;
    data->len = 0;
    if (NULL != data->array) {
        free(data->array);
        data->array = NULL;
    }
    if (NULL != data->_internal) {
        free((struct mysort_simple_2uint_struct *)(data->_internal));
        data->_internal = NULL;
    }
    return 0;
} // end __free_demo

/**
 * allocates memory to store key-value-pairs inside of data-struct
 * number of pairs is given by data->len
 * variants of ordered data: ASCending, DESCending, VAR1 & VAR2
 * VAR1 and VAR2 allow to check if algorithm(s) preserves order
 * ***********************************************************/
int __gen_demo(struct mysort_data_struct *data, int8_t variant) {
    struct mysort_simple_2uint_struct *ptr2uint;

    if ((NULL == data) || (0 == data->len))
        return -1;

    data->array = calloc(data->len, sizeof(void *));
    ptr2uint = calloc(data->len, sizeof(struct mysort_simple_2uint_struct));
    if ((NULL == data->array) || (NULL == ptr2uint))
        return -1;

    data->_internal = (void *)ptr2uint;

    for (uint32_t i = 0; i < data->len; ++i) {
        data->array[i] = &ptr2uint[i];
        switch (variant) {
        case DESC: {
            ptr2uint[i].key = data->len - i - 1;
            ptr2uint[i].value = i;
            break;
        }
        case VAR1: {
            ptr2uint[i].key = data->len - (i - i % 2);
            ptr2uint[i].value = data->len - i - 1;
            break;
        }
        case VAR2: {
            uint64_t a[] = {1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 3, 5, 5, 4, 4};
            ptr2uint[i].key = a[i % 16];
            ptr2uint[i].value = i;
            break;
        }
        default: {
            ptr2uint[i].key = ptr2uint[i].value = i;
            break;
        }
        } // end switch
    }     // end for
    return 0;
} // end __gen_asc_demo

/*
 * Called by sort function(s) (like qsort) to compare
 * two elements of our struct mysort_simple_2uint_struct
 * ***************************************************************  */
int __compare_simple_2uint_structs(const void *left, const void *right) {
    struct mysort_simple_2uint_struct arg1 =
        *(const struct mysort_simple_2uint_struct *)left;
    struct mysort_simple_2uint_struct arg2 =
        *(const struct mysort_simple_2uint_struct *)right;
    if (arg1.key < arg2.key)
        return -1;
    if (arg1.key > arg2.key)
        return 1;
    return 0;
}

/*
 * prints key-value-pairs (KVPs) to stdout
 * prefix: if not NULL -> Line to print before KVPs
 * ***************************************************************  */
void __print_key_value_pairs(struct mysort_data_struct *data,
                             const char *prefix) {
    if (NULL != prefix)
        fprintf(stdout, "%s\n", prefix);
    for (uint32_t i = 0; i < data->len; ++i) {
        struct mysort_simple_2uint_struct *tmp =
            (struct mysort_simple_2uint_struct *)data->array[i];
        fprintf(stdout, "key: %03lu \t value: %03lu at index: %03u\n", tmp->key,
                tmp->value, i);
    } // end for

} // end of __print_key_value_pairs

#ifndef RIPES
/**
 * compute, print and return ns elapsed
 * ***************************************************/
uint64_t __compute_timediff(struct timespec *start, struct timespec *end,
                            uint8_t print) {
    struct timespec temp;
    if ((end->tv_nsec - start->tv_nsec) < 0) {
        temp.tv_sec = end->tv_sec - start->tv_sec - 1;
        temp.tv_nsec = 1000000000 + end->tv_nsec - start->tv_nsec;
    } else {
        temp.tv_sec = end->tv_sec - start->tv_sec;
        temp.tv_nsec = end->tv_nsec - start->tv_nsec;
    }
    uint64_t nanosec = (uint64_t)(temp.tv_sec * 1000000000 + temp.tv_nsec);
    if (print)
        fprintf(stdout, "NS elapsed: %lu ns\n", nanosec);
    return nanosec;
} // end __compute_timediff
#endif

/**
 * orchestrate timing and execution of sort algorithm
 * *************************************************/
int sort_handle_struct(struct handle_struct *h) {
    struct mysort_data_struct data;

    data.len = h->KVPs;
    data.array = data._internal = NULL;

    if (0 != __gen_demo(&data, h->data_variant))
        return -1;

    if (h->verbose)
        __print_key_value_pairs(&data, "Davor");

#ifndef RIPES
    struct timespec start_time, stop_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
#endif

    SORT_FUNCTION_NAME(*data.array, data.len,
                       sizeof(struct mysort_simple_2uint_struct),
                       __compare_simple_2uint_structs);

#ifndef RIPES
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_time);
    h->nanoseconds = __compute_timediff(&start_time, &stop_time, 1);
#endif

    if (h->verbose)
        __print_key_value_pairs(&data, "Danach");

    return __free_demo(&data);
}
