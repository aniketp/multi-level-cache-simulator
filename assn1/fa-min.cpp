#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "cache-min.h"

using namespace std;
namespace fs = std::experimental::filesystem;


void inclusive(shared_ptr<Cache> l2, shared_ptr<CacheMin> l3, int_t addr,
                int index) {
    int_t evicted;
    if (l2->check_hit_or_miss(addr)) {
        (l2->hits)++;
        l2->update_on_hit(addr);
    } else {
        (l2->misses)++;
        if (l3->check_hit_or_miss(addr)) {
            (l3->hits)++;
            l2->add_block(addr);
        } else {
            (l3->misses)++;
            evicted = l3->add_block(addr, index);
            if (evicted && l2->check_hit_or_miss(evicted))
                l2->invalidate_block(evicted);
            l2->add_block(addr);
        }
    }
}

// Process instructions in the trace file and store within a set
// for later use in Belady's Optimal Cache replacement policy.
void preprocess(ifstream& tracestrm, vector <int_t>& min_set) {
    int_t type, address;
    string line;
    while (getline(tracestrm, line)) {
        stringstream line_(line);
        line_ >> type >> address;
        if (type) min_set.emplace_back(address);
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

        // Preprocess tracefile; For Belady's MIN algorithm.
        vector <int_t> min_set;
        ifstream prestrm (tracefile.path());
        preprocess(prestrm, min_set);
        prestrm.close();

        Cache::Ptr l2Incl = make_shared<Cache>(L2Cache, 1024, 8);
        CacheMin::Ptr l3Incl =
                make_shared<CacheMin>(L3Cache, 1, 32768, min_set);

        // Read through the traces and simlulate above declared caches
        // through the corresponding trace.
        cout << "Processing file " << tracefile.path().filename().string()
             << endl;
        int index = 0;
        while (getline(tracestrm, line)) {
            stringstream line_(line);
            line_ >> type >> address;
            // L1 cache missed, forward it to lower levels
            if (type) inclusive(l2Incl, l3Incl, address, index++);
        }

        // TODO: Prettify this, once the simulator works properly
        cout << "------------ " <<  tracefile.path().filename().string()
             << " ------------";
        cout << "\n INCLUSIVE  | L2 Hits:   " << l2Incl->hits;
        cout << "\n INCLUSIVE  | L2 Misses: " << l2Incl->misses;
        cout << "\n INCLUSIVE  | L3 Hits:   " << l3Incl->hits;
        cout << "\n INCLUSIVE  | L3 Misses: " << l3Incl->misses;
        cout << "\n";
    }
    return 0;
}
