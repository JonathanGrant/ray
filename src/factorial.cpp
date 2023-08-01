#include <algorithm>
#include <vector>
#include "factorial.hpp"

std::vector<unsigned int> cache = {0, 1};

unsigned int Factorial(size_t x) {
    if (x <= 1) return std::max<unsigned int>(x, 0);
    for (size_t miss = cache.size(); miss <= x; miss++)
        cache.push_back(cache[miss-1] * miss);
    return cache[x];
}

unsigned int Factorial(int x) {
    if (x < 0) return 0;
    return Factorial(x);
}
