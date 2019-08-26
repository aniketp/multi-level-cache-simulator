#ifndef _CACHE_MIN_H_
#define _CACHE_MIN_H_

#include "cache.h"

class CacheMin {
  public:
    typedef std::shared_ptr<CacheMin> Ptr;

    // ctor
    CacheMin(type level, int num_sets, int num_ways,
            std::vector<int_t>& min_set);

    // dtor
    ~CacheMin() = default;

    // Retrieve block from memory on miss.
    int_t add_block(int_t address, int index);
    
    // Check hit or miss for req. address
    bool check_hit_or_miss(int_t address);
    
    // Evict victim block from cache.
    void invalidate_block(int_t address);

    // Count of hits and misses
    int_t hits = 0, misses = 0;

  private:
    // Cache Heirarchy (L1 or L2).
    type level_;

    // Number of sets in the cache.
    int num_sets_;

    // Number of ways in the cache.
    int num_ways_;

    // 2-d matrix, representing the cache org.
    std::vector <std::vector <cell> > matrix_;

    // Instructions for Belady's optimal policy
    std::vector <int_t> min_set_;
};

# endif  // _CACHE_MIN_H_