#include "cache.h"

int main() {
    Cache l2(L2Cache, 8, 1024);
    Cache l3(L3Cache, 16, 1024);

    int type, addr, evicted;
    int hits, misses;

    if (l2.check_hit_or_miss(addr)) {
        l2.hits++;
        l2.update_on_hit(addr);
    } else {
        l2.misses++;
        if (l3.check_hit_or_miss(addr)) {
            l3.hits++;
            l3.invalidate_block(addr);
            evicted = l2.add_block(addr);
            if(evicted > 0)
                l3.add_block(evicted);
        } else {
            l3.misses++;
            evicted = l2.add_block(addr);
            if (evicted > 0)
                l3.add_block(evicted);
                // EVICTED BLOCK FROM L3 GOES DRAM?????
        }
    }
}