
| Method | Primary Purpose | Scope / What it Measures | Unit / Resolution | Performance Overhead |
| :--- | :--- | :--- | :--- | :--- |
| **`clock_gettime()`** | Measuring elapsed calendar time or continuous intervals. | **Real-world time** passed (Wall time). Can track absolute time (`REALTIME`) or pure duration (`MONOTONIC`). | Nanoseconds | **Low** (Usually a fast `vDSO` system call that stays in user space). |
| **`times()`** | Measuring fundamental CPU consumption. | **CPU time** broken down into User space and Kernel (System) space for the process and its children. | Clock ticks (OS ticks) 1/100th of a second| **Medium** (Requires a standard context switch to the kernel). |
| **`getrusage()`** | Comprehensive resource profiling. | **CPU time** (User & System) + **System resources** (Max RAM/RSS, page faults, I/O context switches). | Microseconds (for CPU time) | **Medium** (Standard system call). |
| **`rdtsc()`** | Low-level micro-benchmarking. | **CPU clock cycles** passed since the processor was reset. | 1 CPU Cycle (Sub-nanosecond) | **Extremely Low** (A single assembly instruction; executes in a few cycles). |


# times()
the kernal timer is 100 ticks per second. run getconf CLK_TCK to check that

| Field | What It Measures |
| :--- | :--- |
| `tms_utime` | **User CPU time**: Amount of time the CPU spent executing instructions in user space for the calling process. |
| `tms_stime` | **System CPU time**: Amount of time the CPU spent executing kernel-space code (like system calls) on behalf of the calling process. |
| `tms_cutime` | **Children User CPU time**: The accumulated user CPU times of all completed, waited-for child processes. |
| `tms_cstime` | **Children System CPU time**: The accumulated system CPU times of all completed, waited-for child processes. |
