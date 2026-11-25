# CPU Cache Research

## Research Topic
Impact of Memory Access Patterns and CPU Cache Hierarchy (L1/L2/L3) on Program Execution Latency.

## Project Description
This project investigates how different memory access patterns affect program execution latency across working set sizes (`32 KB`, 256 KB, 4 MB, and `32 MB`).

The experiment compares:
- Sequential Memory Access
- Strided Memory Access (`stride = 17`)
- Random Memory Access (`std::mt19937(42)`)

The benchmark is implemented in C++ with a warm-up pass, 15 timed repetitions per configuration (reporting the median), averaged across four independent runs.

## Experimental Environment
- System: Gigabyte Gaming A16, Windows 11 Home
- CPU: AMD Ryzen 7 260 (L1: 512 KB, L2: 8 MB, L3: 16 MB)
- Memory: 16.0 GB DDR5, 5600 MT/s (~15.3 GB usable)
- Compiler: GCC 16.2.0 (MSYS2 UCRT64), compiled with -O2

## Files
- cache_experiment.cpp — C++ source code of the benchmark.
- results.csv — mean execution times (in milliseconds) across array sizes and access patterns.
- README.md — project overview, experimental environment, and file descriptions.

## Purpose
The purpose of this research is to examine the relationship between memory access patterns, CPU cache hierarchy, and program execution latency.
