#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct handle_struct
{
    int argc;
    char **argv;

    uint32_t KVPs;
    uint8_t verbose;
    uint8_t data_variant;
    uint64_t nanoseconds; // timediff
};

int pre_process(int argc,char **argv, struct handle_struct *h);
int post_process(struct handle_struct *h);
int sort(struct handle_struct *h);

