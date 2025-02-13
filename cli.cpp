#include "random_ints.hpp"
#include <iostream>
#include <string>
#include <type_traits>

[[nodiscard]]
auto print_range(auto &&range)
    requires std::ranges::input_range<std::decay_t<decltype(range)>>
{
    std::string sep = "[";
    for (const auto &x : range) {
        std::cout << sep << x;
        sep = ", ";
    }
    std::cout << "]\n";
};

auto main(int argc, char **argv) -> int
{
    auto ints = random_ints(10);
    print_range(ints);
}
