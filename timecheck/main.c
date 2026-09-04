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
    long ticks_per_sec = sysconf(_SC_CLK_TCK);

    struct tms now;

    for(volatile int i = 0; i < n; i++){     
           times(&now);    
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
        struct tms t1, t2;

        times(&t1);
        times(&t2);
        
        clock_t tick_diff = t2.tms_utime - t1.tms_utime;
        
        // Convert tick difference to nanoseconds
        int ns = (int)(((double)tick_diff / ticks_per_sec) * 1e9);
        
        if(ns >= 0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }

    return 0;
}