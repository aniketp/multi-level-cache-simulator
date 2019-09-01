/*
 * Copyright (c) 2019, Aditya Rohan
 * Copyright (c) 2019, Aniket Pandey
 * 
 * Submitted to:
 * CS622A: 2019-20 Fall Semester. Assignment 1
 */

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

int_t Cache::add_block(int_t address) {
    int set_num = (int) (address) % num_sets_;
    // Check if a way is free in the set
    for (auto &set : matrix_.at(set_num)) {
        if (set.present) continue;
        // Found an empty slot
        set.present = true;
        set.address = address;
        lru_set_.at(set_num).push_front(address);
        return 0;
    }
    // All 'ways' in the set are valid, evict one
    int_t evict_block = lru_set_.at(set_num).back();
    lru_set_.at(set_num).pop_back();

    for (auto &block : matrix_.at(set_num)) {
        if (block.address != evict_block) continue;
        // Found the block to be evicted
        block.address = address;
        lru_set_.at(set_num).push_front(address);
        return evict_block;
    }
    abort(); // Something bad happened
}

bool Cache::check_hit_or_miss(int_t address) {
    int set_num = (int) (address) % num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if ((block.address == address) && (block.present))
            return true;
    }
    return false;
}

void Cache::invalidate_block(int_t address) {
    int set_num = (int) (address) % num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if (block.address != address) continue;
        // Found the block; Invalidate it
        block.present = false;
        lru_set_.at(set_num).remove(address);
        return;
    }
    abort(); // Something bad happened
}

void Cache::update_on_hit(int_t address) {
    int set_num = (int) (address) % num_sets_;
    // Move the block to the top of LRU set
    lru_set_.at(set_num).remove(address);
    lru_set_.at(set_num).push_front(address);
    return;
}