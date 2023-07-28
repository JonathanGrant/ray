#include <algorithm>
#include "factorial.hpp"

unsigned int Factorial(unsigned int x) {
    if (x <= 1) return std::max<unsigned int>(x, 0);
    return x * Factorial(x-1);
}

