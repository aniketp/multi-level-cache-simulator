#include "cache.h"

int main() {
    Cache l2(L2Cache, 8, 1024);
    Cache l3(L3Cache, 16, 1024);

    int type, addr, evicted;

    if (l2.check_hit_or_miss(addr)) {
        l2.hits++;
        l2.update_on_hit(addr);
    } else {
        l2.misses++;
        if (l3.check_hit_or_miss(addr)) {
            l3.hits++;
            l3.update_on_hit(addr);
            evicted = l2.add_block(addr);
            if (!l3.check_hit_or_miss(evicted))
                l3.add_block(evicted);
        } else {
            l3.misses++;
            l3.add_block(addr);    
            evicted = l2.add_block(addr);
            if (!l3.check_hit_or_miss(evicted))
                l3.add_block(evicted);
        }
    }
}