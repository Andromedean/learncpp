#include <iostream>

double getTowerHeight() {
    std::cout << "tower h: ";
    double height{};
    std::cin >> height;
    return height;
} // gTH()

double heightFallen(double seconds) {
    constexpr double gravity {9.8};
    return gravity * seconds * seconds / 2;
} // hF()

int main() {
    double tHeight {getTowerHeight()};
    std::cout << "after 0 seconds: " << tHeight - heightFallen(0) << '\n';
    std::cout << "after 1 seconds: " << tHeight - heightFallen(1) << '\n';
    std::cout << "after 2 seconds: " << tHeight - heightFallen(2) << '\n';
    std::cout << "after 3 seconds: " << tHeight - heightFallen(3) << '\n';
    std::cout << "after 4 seconds: " << tHeight - heightFallen(4) << '\n';
    std::cout << "after 5 seconds: " << tHeight - heightFallen(5) << '\n';
} // main()
