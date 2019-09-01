# Multi level Cache Simulator
A program to simulate L1 cache misses to a 3 level Cache hierarchy for various
applications. The simulator is programmed for three different cache inclusion
policies, i.e *inclusive*, *exclusive*, *non-inclusive-non-exclusive (NINE)*.

The cache-simulator is developed as a part of the Assignment-1 for the course
Advanced Computer Architecture **(CS622A)**, Fall Semester - 2019, 
instructed by [Prof. Mainak Chaudhury](https://www.cse.iitk.ac.in/users/mainakc/).

The results of the simulation are compiled [here](./result/README.md).
And the project report can be found [here](./docs/report.pdf).

### Group Members (G16)

| __Name__ | __Email__ | __Roll__ |
|-------------|------------|------------|
| Aditya Rohan | [raditya@iitk.ac.in](mailto:raditya@iitk.ac.in) | 160053 |
| Aniket Pandey | [aniketp@iitk.ac.in](mailto:aniketp@iitk.ac.in) | 160113 |


## Build Instructions
Make sure that the L1 miss-traces are present in a directory named
`traces` in the root folder of the project. 
<hr>

**Part 1**: Set associative L2/L3 cache with LRU eviction policy.
``` bash
> make process       # Process miss traces in a relevant format
```

``` bash
> make simulate      # Build and run the simulator on the processed traces
```

**Note:** Do `make part1` to run the above two make commands together. 
Total execution time is about **2.5 Minutes**.
<hr>

**Part 2**: Fully associative L3 cache with LRU/Belady's MIN eviction 
policy.
``` bash
> make fa-lru        # Model FA-L3 cache with LRU Inclusion policy
```

``` bash
> make fa-min        # Model FA-L3 cache with Belady's MIN Inclusion policy
```

**Note:** Do `make part2` to run the above two make commands together.<br>
<hr>

### Warning
Since the Belady's optimal replacement policy looks into the future to 
figure out which block to replace, running it with 10+ million trace 
entries can take huge amount of time. For instance, *sphinx3*, which 
performs terribly with even the best cache organization, can easily take
more than **8 hours** to complete under Belady's MIN policy.
