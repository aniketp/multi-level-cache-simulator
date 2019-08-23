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

#### Definite Output

```
Processing file gcc.log_l1misstrace.out
------------ gcc.log_l1misstrace.out ------------
 INCLUSIVE  | L2 Hits:   6322845
 INCLUSIVE  | L2 Misses: 8287966
 INCLUSIVE  | L3 Hits:   2591153
 INCLUSIVE  | L3 Misses: 5696813

 EXCLUSIVE  | L2 Hits:   6335932
 EXCLUSIVE  | L2 Misses: 8274879
 EXCLUSIVE  | L3 Hits:   3120575
 EXCLUSIVE  | L3 Misses: 5154304

 Non-In/Ex  | L2 Hits:   6335932
 Non-In/Ex  | L2 Misses: 8274879
 Non-In/Ex  | L3 Hits:   2597697
 Non-In/Ex  | L3 Misses: 5677182

Processing file hmmer.log_l1misstrace.out
------------ hmmer.log_l1misstrace.out ------------
 INCLUSIVE  | L2 Hits:   241237
 INCLUSIVE  | L2 Misses: 3268528
 INCLUSIVE  | L3 Hits:   516946
 INCLUSIVE  | L3 Misses: 2751582

 EXCLUSIVE  | L2 Hits:   241658
 EXCLUSIVE  | L2 Misses: 3268107
 EXCLUSIVE  | L3 Hits:   641266
 EXCLUSIVE  | L3 Misses: 2626841

 Non-In/Ex  | L2 Hits:   241658
 Non-In/Ex  | L2 Misses: 3268107
 Non-In/Ex  | L3 Hits:   517202
 Non-In/Ex  | L3 Misses: 2750905

Processing file bzip2.log_l1misstrace.out
------------ bzip2.log_l1misstrace.out ------------
 INCLUSIVE  | L2 Hits:   1664904
 INCLUSIVE  | L2 Misses: 8992723
 INCLUSIVE  | L3 Hits:   1084105
 INCLUSIVE  | L3 Misses: 7908618

 EXCLUSIVE  | L2 Hits:   1665529
 EXCLUSIVE  | L2 Misses: 8992098
 EXCLUSIVE  | L3 Hits:   1256731
 EXCLUSIVE  | L3 Misses: 7735367

 Non-In/Ex  | L2 Hits:   1665529
 Non-In/Ex  | L2 Misses: 8992098
 Non-In/Ex  | L3 Hits:   1084517
 Non-In/Ex  | L3 Misses: 7907581

Processing file h264ref.log_l1misstrace.out
------------ h264ref.log_l1misstrace.out ------------
 INCLUSIVE  | L2 Hits:   545703
 INCLUSIVE  | L2 Misses: 1802870
 INCLUSIVE  | L3 Hits:   164248
 INCLUSIVE  | L3 Misses: 1638622

 EXCLUSIVE  | L2 Hits:   546630
 EXCLUSIVE  | L2 Misses: 1801943
 EXCLUSIVE  | L3 Hits:   204227
 EXCLUSIVE  | L3 Misses: 1597716

 Non-In/Ex  | L2 Hits:   546630
 Non-In/Ex  | L2 Misses: 1801943
 Non-In/Ex  | L3 Hits:   164867
 Non-In/Ex  | L3 Misses: 1637076

Processing file sphinx3.log_l1misstrace.out
------------ sphinx3.log_l1misstrace.out ------------
 INCLUSIVE  | L2 Hits:   438226
 INCLUSIVE  | L2 Misses: 10315221
 INCLUSIVE  | L3 Hits:   365466
 INCLUSIVE  | L3 Misses: 9949755

 EXCLUSIVE  | L2 Hits:   439605
 EXCLUSIVE  | L2 Misses: 10313842
 EXCLUSIVE  | L3 Hits:   515179
 EXCLUSIVE  | L3 Misses: 9798663

 Non-In/Ex  | L2 Hits:   439605
 Non-In/Ex  | L2 Misses: 10313842
 Non-In/Ex  | L3 Hits:   366214
 Non-In/Ex  | L3 Misses: 9947628

Processing file gromacs.log_l1misstrace.out
------------ gromacs.log_l1misstrace.out ------------
 INCLUSIVE  | L2 Hits:   712291
 INCLUSIVE  | L2 Misses: 2719220
 INCLUSIVE  | L3 Hits:   1105404
 INCLUSIVE  | L3 Misses: 1613816

 EXCLUSIVE  | L2 Hits:   714357
 EXCLUSIVE  | L2 Misses: 2717154
 EXCLUSIVE  | L3 Hits:   1215739
 EXCLUSIVE  | L3 Misses: 1501415

 Non-In/Ex  | L2 Hits:   714357
 Non-In/Ex  | L2 Misses: 2717154
 Non-In/Ex  | L3 Hits:   1107486
 Non-In/Ex  | L3 Misses: 1609668
```
