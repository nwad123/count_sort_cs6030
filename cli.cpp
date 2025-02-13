#include "count_sort.hpp"
#include "count_sort_reference.hpp"
#include "random_ints.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>
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

    fmt::println("Original range:   {}", ints);

    // create a copy to test the two implementations
    auto ints_2 = ints;

    count_sort_reference(ints.data(), static_cast<int>(num_ints));
    count_sort(ints_2, num_threads);

    fmt::println("Reference sorted: {}", ints);
    fmt::println("Parallel sorted:  {}", ints_2);
}
