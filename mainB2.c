#include <stdio.h>
#include "time.h"
#include "wait.h"
#include <unistd.h>
#include <string.h>

#define CPU_FREQUENCY_IN_MHZ 600

int main() {
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    long n = 10000000; // 10 million
    struct timespec now;

    for(volatile int i = 0; i < n; i++){     
        clock_gettime(CLOCK_MONOTONIC, &now);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate total time in nanoseconds
    double total_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    double latency_per_read = total_ns / n;

    printf("Average latency: %f ns\n", latency_per_read);

    int ns_max = 50;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);
    

    // resoltion
    for(int i = 0; i < 10*1000*1000; i++){
        struct timespec t1, t2;

        clock_gettime(CLOCK_MONOTONIC, &t1);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        
        int ns = (t2.tv_sec - t1.tv_sec) * 1000000000 + (t2.tv_nsec - t1.tv_nsec);
        
        if(ns >= 0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }

    return 0;
}