#include "random_ints.hpp"
#include <iostream>
#include <string>

auto main() -> int
{
    auto print_range = [](auto &&range) {
        std::string sep = "[";
        for (const auto &x : range) {
            std::cout << sep << x;
            sep = ", ";
        }
        std::cout << "]\n";
    };

    auto ints = random_ints(10);
    print_range(ints);
}
