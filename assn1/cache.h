#ifndef _CACHE_H_
#define _CACHE_H_

#include <list>
#include <vector>

enum type {L1Cache, L2Cache};

struct cell {
    bool present;	// Valid bit
    int address;	// Memory address
};

class Cache {
  public:
    // ctor
    Cache(type level, int num_sets, int num_ways);

    // dtor
    ~Cache() = default;

    // Retrieve block from memory on miss.
    void add_on_miss(int address);
    
    // Evict victim block from cache.
    void invalidate_block(int address);

    // Update LRU table on cache hit.
    void update_on_hit(int address);

  private:
    // Cache Heirarchy (L1 or L2).
    type level_;

    // Number of sets in the cache.
    int num_sets_;

    // Number of ways in the cache.
    int num_ways_;

    // 2-d matrix, representing the cache org.
    std::vector <std::vector <cell> > matrix_;

    // List of sets for recording LRU status.
    std::vector <std::list <int> > lru_set_;
    
};

#endif  // _CACHE_H_