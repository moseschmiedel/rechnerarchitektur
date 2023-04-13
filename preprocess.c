#include "demo.h"
// required for atoi
#include <stdlib.h>
// required for getopt
#include <getopt.h>
// required for isprint
#include <ctype.h>



void _main_preprocess_print_usage(struct handle_struct *h,uint8_t leave)
{
    fprintf(stdout,"%s is a sort demo stub.\n",h->argv[0]);
    fprintf(stdout,"-h\tshowes this help and exit\n");
    fprintf(stdout,"-v\tenable verbose mode\n");
    fprintf(stdout,"-n <KVPs>\tnumber of key-value-pairs\n");
    fprintf(stdout,"\t\t1 < n < 10^6\n");
    fprintf(stdout,"-m <mode>\tdata gen mode\n");
    fprintf(stdout,"\t\t0:ASC\n\t\t1:DESC\n\t\t2:VAR1\n\t\t3:VAR2\n");
    if (1 == leave) exit(0);
}

/**
 * parse commandline options
 * ********************************** */
int _main_preprocess_getopt (struct handle_struct *h)
{
    int c;
    int64_t dflag;

    while ((c = getopt (h->argc, h->argv, "hn:vm:")) != -1)
        switch (c)
        {
        case 'h':
            /* show help and exit */
            _main_preprocess_print_usage(h,1);
            return 1;
            break;
        case 'v':
            /* show help and exit */
            h->verbose = 1;
            fprintf(stderr,"\tVerbose mode enabled\n");
            break;
        case 'n':
            dflag = atoi(optarg);
            if ((1 >= dflag) || (1000000 < dflag))
            {
                fprintf(stderr,"ERROR\n");
                fprintf(stderr,"\t-n [2..1000000] required/allowed but got: %ld\n",dflag);
            }
            else
            {
                h->KVPs=(uint32_t)dflag;
            }
            fprintf(stderr,"\tNumber of key-value-pairs: %u\n",h->KVPs);
            break;
        case 'm':
            dflag = atoi(optarg);
            if ((0 >= dflag) || (3 < dflag))
            {
                fprintf(stderr,"ERROR\n");
                fprintf(stderr,"\tMode %ld ist unknown\n",dflag);
            }
            else
            {
                h->data_variant=(uint8_t)dflag;
            }
            fprintf(stderr,"\tdata generation set to mode: %u\n",h->data_variant);
            break;
        default:
            //abort ();
            break;
        }

    return 0;
}

int pre_process(int argc, char **argv, struct handle_struct *h)
{
    h->argc = argc;
    h->argv = argv;
    /* Defaults */
    h->KVPs = 32;
    h->verbose = 0;
    h->data_variant = 0;
    h->nanoseconds = 0;

    _main_preprocess_getopt(h);
    return 0;
}
