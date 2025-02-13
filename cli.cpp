#include "count_sort.hpp"
#include "count_sort_reference.hpp"
#include "random_ints.hpp"
#include <algorithm>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <iostream>
#include <string>

auto main(int argc, char **argv) -> int
{
    if (argc != 3) {
        fmt::println("Usage: {} <number of threads> <number of ints>", argv[0]);
        return EXIT_FAILURE;
    }

    auto num_threads = std::stoul(argv[1]);
    auto num_ints = std::stoul(argv[2]);

    auto ints = random_ints(num_ints);
    auto ints2 = random_ints(num_ints);

    fmt::println("Random range:     {}\n", ints);

    count_sort_reference(ints.data(), static_cast<int>(ints.size()));
    count_sort(ints2, num_threads);

    fmt::println("Reference sorted: {}", ints);
    fmt::println("Parallel sorted:  {}", ints2);
    fmt::println("\nImplementations {} equal", [&]() {
        if (std::ranges::equal(ints, ints2)) {
            return "are";
        } else {
            return "are not";
        }
    }());
}
