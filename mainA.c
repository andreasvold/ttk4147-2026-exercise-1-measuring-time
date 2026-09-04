#include <stdio.h>
#include "time.h"
#include "wait.h"
#include <unistd.h>

int main() {
    
    struct tms start_tms, end_tms;
    clock_t start_wall, end_wall;
    long ticks_per_sec = sysconf(_SC_CLK_TCK);

    // Get initial times
    start_wall = times(&start_tms);

    struct timespec ts = {.tv_sec = 1, .tv_nsec = 0};
    busy_wait(ts);
    
    // Get final times
    end_wall = times(&end_tms);

    // Calculate differences
    double user_cpu = (double)(end_tms.tms_utime - start_tms.tms_utime) / ticks_per_sec;
    double sys_cpu  = (double)(end_tms.tms_stime - start_tms.tms_stime) / ticks_per_sec;
    double wall_time = (double)(end_wall - start_wall) / ticks_per_sec;

    printf("User CPU Time:   %.4f seconds\n", user_cpu);
    printf("System CPU Time: %.4f seconds\n", sys_cpu);
    printf("Total Wall Time: %.4f seconds\n", wall_time);

    return 0;
}