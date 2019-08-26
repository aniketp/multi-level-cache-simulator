#include <algorithm>
#include <utility>
#include "cache-min.h"
using namespace std;

CacheMin::CacheMin(type level, int num_sets, int num_ways,
                    vector<int_t>& min_set)
            : level_(move(level)),
              num_sets_(move(num_sets)),
              num_ways_(move(num_ways)),
              min_set_(move(min_set)) {
    // Create a 2d array for the cache
    matrix_.resize(num_sets, vector <cell>(num_ways));
};

int_t CacheMin::add_block(int_t address, int index) {
    int set_num = (int) address % num_sets_;
    // Check if a way is free in the set
    for (auto &set : matrix_.at(set_num)) {
        if (set.present) continue;
        // Found an empty slot
        set.present = true;
        set.address = address;
        return 0;
    }
    // All 'ways' in the set are valid, evict one
    int_t max_dist = 0, evict_block = 0;
    for (auto &block : matrix_.at(set_num)) {
        auto itr = find(min_set_.begin() + index,
                    min_set_.end(), block.address);
        int_t pos = distance(min_set_.begin(), itr);
        // This element is farther, update max_dist.
        if (pos > max_dist) {
            max_dist = pos;
            evict_block = &block - &matrix_.at(set_num)[0];
        }
    }
    // Replace the farthest block with the current
    cell victim = matrix_.at(set_num)[evict_block];
    matrix_.at(set_num)[evict_block].address = address;
    return victim.address;
}

bool CacheMin::check_hit_or_miss(int_t address) {
    int set_num = (int) address % num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if ((block.address == address) && (block.present))
            return true;
    }
    return false;
}

void CacheMin::invalidate_block(int_t address) {
    int set_num = (int) address % num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if (block.address != address) continue;
        // Found the block; Invalidate it
        block.present = false;
        return;
    }
    abort(); // Something bad happened
}
