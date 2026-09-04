#include <stdio.h>
#include "time.h"
#include "wait.h"
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#define CPU_FREQUENCY_IN_MHZ 600

/*
------------------------
ON RASPBERRY PI USE THIS
------------------
uint64_t rdtsc(void){
    uint64_t val;
    asm volatile("isb; mrs %0, cntvct_el0; isb; " : "=r"(val) :: "memory"); 
    // You can check the current CPU frequency with $sudo dmesg | grep MHz
    return val;
}
*/

//    USE THIS ON PC
uint64_t rdtsc(void) {
    unsigned int lo, hi;
    // On x86_64, rdtsc puts the lower 32 bits in EAX and upper 32 bits in EDX
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    
    long n = 10000000; // 10 million
    
    uint64_t start_cycles = rdtsc();

    for(volatile int i = 0; i < n; i++){     
        rdtsc();
    }

    uint64_t end_cycles = rdtsc();

    uint64_t total_cycles = end_cycles - start_cycles;
    double cycles_per_read = (double)total_cycles / n;
    
    double total_seconds = (double)total_cycles / (CPU_FREQUENCY_IN_MHZ * 1000000.0);

    printf("Total cpu cycles: %lu\n", total_cycles);
    printf("Average cycles per iteration: %.2f\n", cycles_per_read);

    printf("Number of seconds: %.9f\n", total_seconds);
    printf("Average seconds per iteration: %.9f\n", total_seconds*1000000000/n);



    int ns_max = 50;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);

    // resoltion
    for(int i = 0; i < 10*1000*1000; i++){
        
        uint64_t t1 = rdtsc();
        uint64_t t2 = rdtsc();
        
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