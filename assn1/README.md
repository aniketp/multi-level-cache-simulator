### Multi level Cache Simulator
A program to simulate L1 cache misses to a 3 level Cache hierarchy for various
applications. The simulator is programmed for three different cache inclusion
policies, i.e *inclusive*, *exclusive*, *non-inclusive-non-exclusive*.

Made as a part of Assignment-1 for the course Advanced Computer Architecture
**(CS622A)** Fall Semester - 2019, instructed by Prof. Mainak Chaudhary.

#### Group Members (G16)

| __Name__ | __Email__ | __Roll__ |
|-------------|------------|------------|
| Aditya Rohan | [raditya@iitk.ac.in](mailto:raditya@iitk.ac.in) | 160053 |
| Aniket Pandey | [aniketp@iitk.ac.in](mailto:aniketp@iitk.ac.in) | 160113 |


#### Build Instruction
``` bash
 make process       # Process miss traces; Build simulator
```

``` bash
 make run           # Run the simulator on processed traces
```

**Note:** Do `make all` to avoid any hardwork!