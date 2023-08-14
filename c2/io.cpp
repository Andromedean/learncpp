#include "io.h"
#include <iostream>

int readNumber() {
    int input {};

    std::cin >> input;

    return input;
}

void writeAnswer(int n) {
    std::cout << "Answer: " << n << '\n';
}
