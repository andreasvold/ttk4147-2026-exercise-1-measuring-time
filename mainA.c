#include <stdio.h>
#include "time.h"
#include "wait.h"

int main() {

    // sleep(1);
    struct timespec ts = {.tv_sec = 1, .tv_nsec = 0};
    busy_wait_times(ts);
    /*
    busy_wait(ts);
    */

    return 0;
}