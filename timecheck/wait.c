#include "wait.h"
#include "time.h"
#include <stdio.h>

void busy_wait(struct timespec t){
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    struct timespec then = timespec_add(now, t);
    
    while(timespec_cmp(now, then) < 0){
        for(int i = 0; i < 10000; i++){}
        clock_gettime(CLOCK_MONOTONIC, &now);
    }
}

void busy_wait_times(struct timespec t){
    struct tms now;
    struct timespec tmespeck;
    times(&now);

    long ticks_per_sec = sysconf(_SC_CLK_TCK);
    double user_seconds = (double)now.tms_utime / ticks_per_sec;

    tmespeck.tv_sec = (time_t) user_seconds;                     
    tmespeck.tv_nsec = (long)((user_seconds - tmespeck.tv_sec) * 1000000000); 

    struct timespec then = timespec_add(tmespeck, t);


    
    while(timespec_cmp(tmespeck, then) < 0){
        for(int i = 0; i < 10000; i++){}
        times(&now);    
        long ticks_per_sec = sysconf(_SC_CLK_TCK);
        double user_seconds = (double)now.tms_utime / ticks_per_sec;

        tmespeck.tv_sec = (time_t) user_seconds;                     
        tmespeck.tv_nsec = (long)((user_seconds - tmespeck.tv_sec) * 1000000000);
        
        }
}