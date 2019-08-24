#include <algorithm>
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;
namespace fs = std::experimental::filesystem;
typedef unsigned long long int_t;

enum type {L2Cache, L3Cache};

struct cell {
    bool present;	// Valid bit
    int_t address;	// Memory address
};

class Cache {
  public:
    typedef std::shared_ptr<Cache> Ptr;

    // ctor
    Cache(type level, int num_sets, int num_ways);

    // dtor
    ~Cache() = default;

    // Retrieve block from memory on miss.
    int_t add_block(int_t address);
    
    // Check hit or miss for req. address
    bool check_hit_or_miss(int_t address);
    
    // Evict victim block from cache.
    void invalidate_block(int_t address);

    // Update LRU table on cache hit.
    void update_on_hit(int_t address);

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

    // List of sets for recording LRU status.
    std::vector <std::list <int_t> > lru_set_;
    
};

Cache::Cache(type level, int num_sets, int num_ways)
            : level_(move(level)),
              num_sets_(move(num_sets)),
              num_ways_(move(num_ways)) {
    // Create a 2d array and LRU record for the cache
    matrix_.resize(num_sets, vector <cell>(num_ways));
    lru_set_.resize(num_sets);
};

int_t Cache::add_block(int_t address) {
    int set_num = (int) address % num_sets_;
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
    cout << "lol\n";
    // abort(); // Something bad happened
}

bool Cache::check_hit_or_miss(int_t address) {
    int set_num = (int) address % num_sets_;
    for (auto &block : matrix_.at(set_num)) {
        if (block.address == address) return true;
    }
    return false;
}

void Cache::invalidate_block(int_t address) {
    int set_num = (int) address % num_sets_;
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
    int set_num = (int) address % num_sets_;
    // Move the block to the top of LRU set
    lru_set_.at(set_num).remove(address);
    lru_set_.at(set_num).push_front(address);
    return;
}

//-----------------------------------------------------------------------------

void inclusive(shared_ptr<Cache> l2, shared_ptr<Cache> l3, int_t addr) {
    int_t evicted;
    if (l2->check_hit_or_miss(addr)) {
        (l2->hits)++;
        l2->update_on_hit(addr);
    } else {
        (l2->misses)++;
        if (l3->check_hit_or_miss(addr)) {
            (l3->hits)++;
            l3->update_on_hit(addr);
            l2->add_block(addr);
        } else {
            (l3->misses)++;
            evicted = l3->add_block(addr);
            if (evicted && l2->check_hit_or_miss(evicted))
                l2->invalidate_block(evicted);
            l2->add_block(addr);
        }
    }
}

int main() {
    int_t type, address;
    string line, folder = "output";
    for (const auto& tracefile : fs::directory_iterator(folder)) {
        ifstream tracestrm (tracefile.path());
        if (!tracestrm.is_open())
            cerr << "Tracefile " << tracefile.path().filename().string()
                 << " could not be opened\n";

        // Create shared pointers to the cache hierarchy for all
        // different inclusion/exclusion policies.
        Cache::Ptr l2Incl = make_shared<Cache>(L2Cache, 1024, 8);
        Cache::Ptr l3Incl = make_shared<Cache>(L3Cache, 1, 32768);
        // Cache::Ptr l2Excl = make_shared<Cache>(L2Cache, 1024, 8);
        // Cache::Ptr l3Excl = make_shared<Cache>(L3Cache, 2048, 16);
        // Cache::Ptr l2Nine = make_shared<Cache>(L2Cache, 1024, 8);
        // Cache::Ptr l3Nine = make_shared<Cache>(L3Cache, 2048, 16);

        // Read through the traces and simlulate above declared caches
        // through the corresponding trace.
        cout << "Processing file " << tracefile.path().filename().string()
             << endl;
        while (getline(tracestrm, line)) {
            stringstream line_(line);
            line_ >> type >> address;
            // L1 cache missed, forward it to lower levels
            if (type) {
                inclusive(l2Incl, l3Incl, address);
                // exclusive(l2Excl, l3Excl, address);
                // nine(l2Nine, l3Nine, address);
            }
        }

        // TODO: Prettify this, once the simulator works properly
        cout << "------------ " <<  tracefile.path().filename().string()
             << " ------------";
        cout << "\n INCLUSIVE  | L2 Hits:   " << l2Incl->hits;
        cout << "\n INCLUSIVE  | L2 Misses: " << l2Incl->misses;
        cout << "\n INCLUSIVE  | L3 Hits:   " << l3Incl->hits;
        cout << "\n INCLUSIVE  | L3 Misses: " << l3Incl->misses;
        // cout << "\n";
        // cout << "\n EXCLUSIVE  | L2 Hits:   " << l2Excl->hits;
        // cout << "\n EXCLUSIVE  | L2 Misses: " << l2Excl->misses;
        // cout << "\n EXCLUSIVE  | L3 Hits:   " << l3Excl->hits;
        // cout << "\n EXCLUSIVE  | L3 Misses: " << l3Excl->misses;
        // cout << "\n";
        // cout << "\n Non-In/Ex  | L2 Hits:   " << l2Nine->hits;
        // cout << "\n Non-In/Ex  | L2 Misses: " << l2Nine->misses;
        // cout << "\n Non-In/Ex  | L3 Hits:   " << l3Nine->hits;
        // cout << "\n Non-In/Ex  | L3 Misses: " << l3Nine->misses;
        // cout << "\n";
    }
    return 0;
}
