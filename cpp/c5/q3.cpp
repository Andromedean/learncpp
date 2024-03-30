#include <iostream>

std::int64_t getInt() {
    std::cout << "enter an int: ";

    std::int64_t n {};
    std::cin >> n;
    return n;
} // getInt()

bool isEven(std::int64_t n) {
    return ((n & 1) == 0);
} // isEven()

int main() {
    std::cout << isEven(getInt()) << '\n';
} // main()
