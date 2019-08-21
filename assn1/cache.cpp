#include <algorithm>
#include <utility>
#include "cache.h"

using namespace std;

Cache::Cache(type level, int num_sets, int num_ways)
            : level_(move(level)),
              num_sets_(move(num_sets)),
              num_ways_(move(num_ways)) {
    // Create a 2d array and LRU record for the cache
    matrix_.resize(num_sets, vector <cell>(num_ways));
    lru_set_.resize(num_sets);
};

int Cache::add_block(int address) {
    int set_num = (int) address/num_sets_;
    // Check if a way is free in the set
    for (auto &set : matrix_.at(set_num)) {
        if (set.present) continue;
        // Found an empty slot
        set.present = true;
        set.address = address;
        lru_set_.at(set_num).push_front(address);
        return -1;
    }
    // All 'ways' in the set are valid, evict one
    int evict_block = lru_set_.at(set_num).back();
    lru_set_.at(set_num).pop_back();

    for (auto &block : matrix_.at(set_num)) {
        if (block.address != evict_block) continue;
        // Found the block to be evicted
        block.address = address;
        lru_set_.at(set_num).push_front(address);
        return address;
    }
    abort(); // Something bad happened
    //return evcted address
}
bool Cache::check_hit_or_miss(int address){
    int set_num = (int) address/num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if (block.address != address) continue;
        return true;
    }
    return false;
}
void Cache::invalidate_block(int address) {
    int set_num = (int) address/num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if (block.address != address) continue;
        // Found the block; Invalidate it
        block.present = false;
        auto index = find(lru_set_.at(set_num).begin(),
                        lru_set_.at(set_num).end(), address);
        lru_set_.at(set_num).erase(index);
        return;
    }
    abort(); // Something bad happened
}

void Cache::update_on_hit(int address) {
    int set_num = (int) address/num_sets_;
    // Move the block to the top of LRU set
    auto index = find(lru_set_.at(set_num).begin(),
                        lru_set_.at(set_num).end(), address);
    lru_set_.at(set_num).erase(index);
    lru_set_.at(set_num).push_front(address);
    return;
}

int main() {
    Cache l1(L1Cache, 1024, 8);
    return 0;
}