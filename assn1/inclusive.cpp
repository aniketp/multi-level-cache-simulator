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
            l3.update_on_hit(addr);
            l2.add_block(addr);
        } else {
            l3.misses++;
            evicted = l3.add_block(addr);
            if (evicted > 0)
                l2.invalidate_block(evicted);
            l2.add_block(addr);
        }
    }
}