#include <sched.h>

#include <stdio.h>
#include "time.h"
#include "wait.h"
#include <unistd.h>
#include <string.h>

int main() {
    struct timespec start, end;
    long n = 100000000; // 100 million
    double sum_time = 0.0;

    for(volatile int i = 0; i < n; i++){     
        clock_gettime(CLOCK_MONOTONIC, &start);
        sched_yield();
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum_time = sum_time + (end.tv_sec - start.tv_sec)*1e9 + (end.tv_nsec - start.tv_nsec);
    }

    // Calculate total time in nanoseconds
    double total_ns = sum_time;
    double latency_per_read = total_ns / n;

    printf("Average latency: %f ns\n", latency_per_read);
    return 0;
}