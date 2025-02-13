#include "random_ints.hpp"
#include <fmt/core.h>
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
    if (argc != 3) {
        fmt::println("Usage: {} <number of threads> <number of ints>", argv[0]);
        return EXIT_FAILURE;
    }

    auto num_threads = std::stoul(argv[1]);
    auto num_ints = std::stoul(argv[2]);

    auto ints = random_ints(num_ints);
    print_range(ints);
}
