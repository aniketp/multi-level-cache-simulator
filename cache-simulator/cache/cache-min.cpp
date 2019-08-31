/*
 * Copyright (c) 2019, Aditya Rohan
 * Copyright (c) 2019, Aniket Pandey
 * 
 * Submitted to:
 * CS622A: 2019-20 Fall Semester. Assignment 1
 */

#include <climits>
#include <algorithm>
#include <sstream>
#include <utility>
#include "cache-min.h"
using namespace std;

CacheMin::CacheMin(type level, int num_ways)
            : level_(move(level)),
              num_ways_(move(num_ways)) {
    // Create a 2d array for the cache
    matrix_.resize(L3_FA_WAY, vector <cell>(num_ways));
};

int_t CacheMin::add_block(int_t address, int index) {
    // Check if a way is free in the set
    for (auto &set : matrix_.at(0)) { 
        if (set.present) continue;
        // Found an empty slot
        set.present = true;
        set.address = address;

        // Find out the next access time for this block.
        while (min_set_[address].size() &&
                (index >= min_set_[address].front())) {
            min_set_[address].erase(min_set_[address].begin());
        }
        // If this block is never accessed in the future, store Infinity.
        if (min_set_[address].empty())
            time_set_.insert({ INT_MAX - (infinity++), address });
        else
            time_set_.insert({ min_set_[address].front(), address });

        return 0;
    }
    // All 'ways' in the set are valid, evict one
    auto evict_itr = time_set_.end();
    for (auto &block : matrix_.at(0)) {
        if (block.address != evict_itr->second) continue;
        block.address = address;

        while (min_set_[address].size() &&
                (index >= min_set_[address].front())) {
            min_set_[address].erase(min_set_[address].begin());
        }
        // If this block is never accessed in the future, store Infinity.
        if (min_set_[address].empty())
            time_set_.insert({ INT_MAX - (infinity++), address });
        else
            time_set_.insert({ min_set_[address].front(), address });

    }
    // Replace the farthest block with the current one.
    int_t victim = evict_itr->second;
    time_set_.erase(evict_itr->first);
    return victim;
}

bool CacheMin::check_hit_or_miss(int_t address) {
    for (auto &block : matrix_.at(0)) {
        if ((block.address == address) && (block.present))
            return true;
    }
    return false;
}

// TODO: FIX THIS
void CacheMin::invalidate_block(int_t address) {
    for (auto &block : matrix_.at(0)) {
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
        address = address >> BLOCK_OFFSET;
        if (type) min_set_[address].emplace_back(index++);
    }
    return index;
}