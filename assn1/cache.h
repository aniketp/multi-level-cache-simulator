#ifndef _CACHE_H_
#define _CACHE_H_

#include <vector>

enum type {L1Cache, L2Cache};

struct cell {
    int present;	// Valid bit
    int address;	// Memory address
};

class Cache {
  public:
    // ctor
    Cache(type level, int num_sets, int num_ways);

    // dtor
    ~Cache() = default;

  private:
    // Cache Heirarchy (L1 or L2).
    type level_;

    // Number of sets in the cache.
    int num_sets_;

    // Number of ways in the cache.
    int num_ways_;

    // 2-d matrix, representing the cache org.
    std::vector <std::vector <cell> > matrix;
};

#endif  // _CACHE_H_