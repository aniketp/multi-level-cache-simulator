#include <algorithm>
#include <sstream>
#include <utility>
#include "cache-min.h"
using namespace std;

CacheMin::CacheMin(type level, int num_sets, int num_ways)
            : level_(move(level)),
              num_sets_(move(num_sets)),
              num_ways_(move(num_ways)) {
    // Create a 2d array for the cache
    matrix_.resize(num_sets, vector <cell>(num_ways));
};

int_t CacheMin::add_block(int_t address, int index) {
    int set_num = (int) (address>>6) % num_sets_;
    // Check if a way is free in the set
    for (auto &set : matrix_.at(set_num)) {
        if (set.present) continue;
        // Found an empty slot
        set.present = true;
        set.address = address;
        return 0;
    }
    // All 'ways' in the set are valid, evict one
    int max_dist = 0, evict_block = 0;
    for (int_t i = 0; i < matrix_.at(set_num).size(); ++i) {
        auto block = matrix_.at(set_num)[i];
        // Make sure there are elements in min_set_[block.address].
        while (min_set_[block.address].size() &&
                (index >= min_set_[block.address].front())) {
            min_set_[block.address].erase(min_set_[block.address].begin());
        }
        // If there is no access for this block in the future, return it.
        if (min_set_[block.address].empty()) {
            evict_block = i;
            break;
        }
        // All addresses before index have been deleted.
        if (max_dist < min_set_[block.address].front() - index) {
            max_dist = min_set_[block.address].front() - index;
            evict_block = i;
        }
    }
    // Replace the farthest block with the current one.
    cell victim = matrix_.at(set_num)[evict_block];
    matrix_.at(set_num)[evict_block].address = address;
    return victim.address;
}

bool CacheMin::check_hit_or_miss(int_t address) {
    int set_num = (int) (address>>6) % num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if ((block.address == address) && (block.present))
            return true;
    }
    return false;
}

void CacheMin::invalidate_block(int_t address) {
    int set_num = (int) (address>>6) % num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if (block.address != address) continue;
        // Found the block; Invalidate it
        block.present = false;
        return;
    }
    abort(); // Something bad happened
}

// Process instructions in the trace file and store within a set
// for later use in Belady's Optimal Cache replacement policy.
int CacheMin::preprocess(ifstream& tracestrm) {
    int_t type, address;
    int index = 0;
    string line;
    while (getline(tracestrm, line)) {
        stringstream line_(line);
        line_ >> type >> address;
        if (type) min_set_[address].emplace_back(index++);
    }
    return index;
}