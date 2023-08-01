#include "myheader.h"
#include <iostream>
#include <cstdlib>  // for atoi and atof
#include "matrix.hpp"

int main(int argc, char *argv[]) {
    if(argc != 4) {  // We expect 3 arguments (besides the program name)
        std::cerr << "Usage: " << argv[0] << " <integer> <float> <string>\n";
        return 1;
    }

    int myInt = std::atoi(argv[1]);
    float myFloat = std::atof(argv[2]);
    std::string myString = argv[3];

    std::cout << "Integer: " << myInt << "\n";
    std::cout << "Float: " << myFloat << "\n";
    std::cout << "String: " << myString << "\n";

    return 0;
}
