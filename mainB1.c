#include <stdio.h>
#include "time.h"
#include "wait.h"
#include <unistd.h>

uint64_t rdtsc(void){
    uint64_t val;
    asm volatile("isb; mrs %0, cntvct_el0; isb; " : "=r"(val) :: "memory"); 
    // You can check the current CPU frequency with $sudo dmesg | grep MHz
    return val;
}

int main() {
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    long n = 10000000; // 10 million
    
    for(volatile int i = 0; i < n; i++){     
        uint64_t t1 = rdtsc();[cite: 1];
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate total time in nanoseconds
    double total_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    double latency_per_read = total_ns / n;

    printf("Average latency: %f ns\n", latency_per_read);

    int ns_max = 50;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);
    
    uint64_t t1 = rdtsc();[cite: 1];
    uint64_t t = rdtsc();[cite: 1];

    // resoltion
    for(int i = 0; i < 10*1000*1000; i++){
        
        uint64_t t1 = rdtsc();[cite: 1]
        uint64_t t2 = rdtsc();[cite: 1]
        
        int ns = (t2 - t1) * 1000.0/CPU_FREQUENCY_IN_MHZ;
        
        if(ns >= 0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }

    return 0;
}