#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "cache.h"

using namespace std;
namespace fs = std::experimental::filesystem;

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

void exclusive(shared_ptr<Cache> l2, shared_ptr<Cache> l3, int_t addr) {
    int_t evicted;
    if (l2->check_hit_or_miss(addr)) {
        (l2->hits)++;
        l2->update_on_hit(addr);
    } else {
        (l2->misses)++;
        if (l3->check_hit_or_miss(addr)) {
            (l3->hits)++;
            l3->invalidate_block(addr);
            evicted = l2->add_block(addr);
            if(evicted > 0)
                l3->add_block(evicted);
        } else {
            (l3->misses)++;
            evicted = l2->add_block(addr);
            if (evicted > 0)
                l3->add_block(evicted);
        }
    }
}

void nine(shared_ptr<Cache> l2, shared_ptr<Cache> l3, int_t addr) {
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
            l3->add_block(addr);    
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
        Cache::Ptr l3Incl = make_shared<Cache>(L3Cache, 2048, 16);
        Cache::Ptr l2Excl = make_shared<Cache>(L2Cache, 1024, 8);
        Cache::Ptr l3Excl = make_shared<Cache>(L3Cache, 2048, 16);
        Cache::Ptr l2Nine = make_shared<Cache>(L2Cache, 1024, 8);
        Cache::Ptr l3Nine = make_shared<Cache>(L3Cache, 2048, 16);

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
                exclusive(l2Excl, l3Excl, address);
                nine(l2Nine, l3Nine, address);
            }
        }

        // TODO: Prettify this, once the simulator works properly
        cout << "------------ " <<  tracefile.path().filename().string()
             << " ------------";
        cout << "\n INCLUSIVE  | L2 Hits:   " << l2Incl->hits;
        cout << "\n INCLUSIVE  | L2 Misses: " << l2Incl->misses;
        cout << "\n INCLUSIVE  | L3 Hits:   " << l3Incl->hits;
        cout << "\n INCLUSIVE  | L3 Misses: " << l3Incl->misses;
        cout << "\n";
        cout << "\n EXCLUSIVE  | L2 Hits:   " << l2Excl->hits;
        cout << "\n EXCLUSIVE  | L2 Misses: " << l2Excl->misses;
        cout << "\n EXCLUSIVE  | L3 Hits:   " << l3Excl->hits;
        cout << "\n EXCLUSIVE  | L3 Misses: " << l3Excl->misses;
        cout << "\n";
        cout << "\n Non-In/Ex  | L2 Hits:   " << l2Nine->hits;
        cout << "\n Non-In/Ex  | L2 Misses: " << l2Nine->misses;
        cout << "\n Non-In/Ex  | L3 Hits:   " << l3Nine->hits;
        cout << "\n Non-In/Ex  | L3 Misses: " << l3Nine->misses;
        cout << "\n";
    }
    return 0;
}
