#include "count_sort.hpp"
#include "count_sort_reference.hpp"
#include "random_ints.hpp"
#include <algorithm>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <string>

const size_t MAX_TO_PRINT = 20;

// `p` 
// Limits the size of a range by wrapping it in a span so that we don't 
// accidentally try to print 100000 elements to the console.
auto p(auto &&range, const size_t max_elem = MAX_TO_PRINT)
{
    if (range.size() > max_elem) {
        return std::span{ range }.subspan(0, max_elem);
    } else {
        return std::span{ range };
    }
}

auto main(int argc, char **argv) -> int
{
    // check command line arguments
    if (argc != 3) {
        fmt::println("Usage: {} <number of threads> <number of ints>", argv[0]);
        return EXIT_FAILURE;
    }

    // parse the number of threads and number of integers to sort from the 
    // command line
    auto num_threads = std::stoul(argv[1]);
    auto num_ints = std::stoul(argv[2]);

    if (num_ints > MAX_TO_PRINT) { fmt::println("Large input size, only 20 elements printed\n"); }

    // generate the input ranges, since the sort is completed in place, we 
    // need to have two copies
    auto ints = random_ints(num_ints);
    auto ints2 = random_ints(num_ints);

    fmt::println("Random range:     {}\n", p(ints));

    // Test the serial reference implementation
    count_sort_reference(ints.data(), static_cast<int>(ints.size()));
    fmt::println("Reference sorted: {}", p(ints));

    // Test the parallel implementation
    count_sort(ints2, num_threads);
    fmt::println("Parallel sorted:  {}", p(ints2));
   
    // Check if the implementations are equal or not
    fmt::println("\nImplementations {} equal", [&]() {
        if (std::ranges::equal(ints, ints2)) {
            return "are";
        } else {
            return "are not";
        }
    }());
}
