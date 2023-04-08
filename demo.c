#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASC 0
#define DESC 1
#define VAR1 2
#define VAR2 3

/* struct holds the array to sort/sorted */
struct mysort_data_struct {
	uint32_t len;		// the number of elements in array
	void **array;		// sortable pointers to the origin array
	void *_internal;	// points to the origin array
};

/* defines the struct of one element in the array to sort */
struct mysort_simple_2uint_struct {
	uint64_t key;
	uint64_t value;
};

/**
 * allocated memory must be freed after usage
 * call __free_demo() to clean up
 * ***********************************************************/
int __free_demo(struct mysort_data_struct *data)
{
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
}				// end __free_demo

/**
 * allocates memory to store key-value-pairs inside of data-struct
 * number of pairs is given by data->len
 * variants of ordered data: ASCending, DESCending, VAR1 & VAR2
 * VAR1 and VAR2 allow to check if algorithm(s) preserves order
 * ***********************************************************/
int __gen_demo(struct mysort_data_struct *data, int8_t variant)
{
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
		case DESC:
			{
				ptr2uint[i].key = data->len - i - 1;
				ptr2uint[i].value = i;
				break;
			}
		case VAR1:
			{
				ptr2uint[i].key = data->len - (i - i % 2);
				ptr2uint[i].value = data->len - i - 1;
				break;
			}
		case VAR2:
			{
				uint64_t a[] =
				    { 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 3, 5, 5,
					4, 4
				};
				ptr2uint[i].key = a[i % 16];
				ptr2uint[i].value = i;
				break;
			}
		default:
			{
				ptr2uint[i].key = ptr2uint[i].value = i;
				break;
			}
		}		// end switch
	}			// end for
	return 0;
}				// end __gen_asc_demo

/* 
 * Called by sort function(s) (like qsort) to compare
 * two elements of our struct mysort_simple_2uint_struct
 * ***************************************************************  */
int __compare_simple_2uint_structs(const void *left, const void *right)
{
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
			     const char *prefix)
{
	if (NULL != prefix)
		fprintf(stdout, "%s\n", prefix);
	for (uint32_t i = 0; i < data->len; ++i) {
		struct mysort_simple_2uint_struct *tmp =
		    (struct mysort_simple_2uint_struct *)data->array[i];
		fprintf(stdout, "key: %03lu \t value: %03lu at index: %03u\n",
			tmp->key, tmp->value, i);
	}			// end for

}				// end of __print_key_value_pairs

/**
 * compute, print and return ns elapsed
 * ***************************************************/
uint64_t __compute_timediff(struct timespec *start, struct timespec *end,
			    uint8_t print)
{
	struct timespec temp;
	if ((end->tv_nsec - start->tv_nsec) < 0) {
		temp.tv_sec = end->tv_sec - start->tv_sec - 1;
		temp.tv_nsec = 1000000000 + end->tv_nsec - start->tv_nsec;
	} else {
		temp.tv_sec = end->tv_sec - start->tv_sec;
		temp.tv_nsec = end->tv_nsec - start->tv_nsec;
	}
	uint64_t nanosec = (uint64_t) (temp.tv_sec * 1000000000 + temp.tv_nsec);
	if (print)
		fprintf(stdout, "NS elapsed: %lu ns\n", nanosec);
	return nanosec;
}				// end __compute_timediff

/* **************************************************
 * MAIN
 * ************************************************** */
int main(int argc, char **argv)
{

	struct mysort_data_struct data;

	data.len = 10000000;
	data.array = data._internal = NULL;

	if (0 != __gen_demo(&data, VAR2))
		return -1;

	if (1 != argc)
		__print_key_value_pairs(&data, "Davor");

	struct timespec start_time, stop_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);

	qsort(*data.array, data.len,
	      sizeof(struct mysort_simple_2uint_struct),
	      __compare_simple_2uint_structs);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_time);
	__compute_timediff(&start_time, &stop_time, 1);

	if (1 != argc)
		__print_key_value_pairs(&data, "Danach");

	return __free_demo(&data);

}				// end main
