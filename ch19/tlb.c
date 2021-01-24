#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

#define PAGESIZE 4096


int main (int argc, char** argv) {
    int MAX_NUMPAGES = (int) strtol(argv[1], (char**)NULL, 10);
    int NUMPAGES = 1;
    long* times = (long*) calloc(MAX_NUMPAGES, sizeof(long));


    struct timespec start, finish;
    int numloops = 10;
    int jump = PAGESIZE / sizeof(int);
    long seconds = 0;
    long ns = 0;
    long ns_avg = 0;

    int l,i;

        /* vary number of pages and array size and time
         * array access
         */
    for (NUMPAGES = 1; NUMPAGES <= MAX_NUMPAGES; NUMPAGES++)
    {
        int* a = (int*) calloc(NUMPAGES*PAGESIZE, sizeof(int));

        for (l = 0; l < numloops; l++)
        {
                /* timer array access */
            clock_gettime(CLOCK_REALTIME, &start);
            for (i = 0; i < NUMPAGES * jump; i += jump)
                a[i] += 1;

            clock_gettime(CLOCK_REALTIME, &finish);

                /* figure out time elapsed */
            seconds = finish.tv_sec - start.tv_sec;
            ns = finish.tv_nsec - start.tv_nsec;
            if (start.tv_nsec > finish.tv_nsec) // clock underflow
            {
                --seconds;
                ns += 1000000000;
            }

            ns_avg += ns; // update average, divide after loop
        }
        ns_avg /= numloops;
        times[NUMPAGES-1] = ns_avg;
        ns_avg = 0;
        free(a);
    }

    for (i = 0; i < MAX_NUMPAGES; i++)
        printf("%d %lu\n", i, times[i]);
    
    return 0;
}
