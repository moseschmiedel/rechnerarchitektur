#include "demo.h"

int post_process(struct handle_struct *h)
{
    if (h->verbose) fprintf(stdout,"primary computing required %lu Nanoseconds\n",h->nanoseconds);

    // free allocated memory here, if required

    return 0;
}
