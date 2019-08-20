#include <utility>
#include "cache.h"

using namespace std;

Cache::Cache(type level, int num_sets, int num_ways)
            : level_(move(level)),
              num_sets_(move(num_sets)),
              num_ways_(move(num_ways)) {
    // Create a 2d array for the cache
    matrix.resize(num_sets, vector <cell>(num_ways));
};

int main() {
    Cache l1(L1Cache, 1024, 8);
    return 0;
}