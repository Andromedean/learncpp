#include <iostream>
#include <string>

int main() {
    std::cout << "enter your full name: ";
    std::string name;
    std::getline(std::cin, name);
    std::cout << "enter your age: ";
    int age {};
    std::cin >> age;

    //std::cout << "age + len of name = " << age + static_cast<int>(name.length()) << '\n';
    std::cout << "age + len of name = " << age + std::size(name) << '\n';
}
