#include <stdio.h>
#include "time.h"
#include "wait.h"
#include <unistd.h>
#include <string.h>

#define CPU_FREQUENCY_IN_MHZ 600

int main() {
    
    struct tms start, end;
    times(&start);
    long n = 10000000; // 10 million
    long ticks_per_sec = sysconf(_SC_CLK_TCK);

    struct tms now;

    for(volatile int i = 0; i < n; i++){     
           times(&now);    
    }

    times(&end);

    // Calculate total time in nanoseconds
    double total_ns = (end.tms_utime - start.tms_utime) * 1e9 + (end.tms_utime - start.tms_utime);
    double latency_per_read = total_ns / n;

    printf("Average latency: %f ns\n", latency_per_read);

    int ns_max = 50;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);

    int n_res = 1e7;
    int sum_counts_included = 0;
    

    // resoltion
    for(int i = 0; i < n_res; i++){
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

    printf("\n%-15s | %s\n", "Nanoseconds", "Count");
    printf("---------------------------\n");

    for(int i = 0; i < ns_max; i++){
        // Only print rows that actually captured measurements
        if(histogram[i] > 0) {
            printf("%-15d | %d\n", i, histogram[i]);
            sum_counts_included += histogram[i];

        }
    }
    printf("---------------------------\n");
    
    printf("Number of resolution checks not included in hist: %d \n", n_res-sum_counts_included);

    return 0;

}