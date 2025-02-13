#include "count_sort.hpp"
#include "fmt/base.h"
#include <ranges>
#ifdef _OPENMP
#include <omp.h>
#endif

// See count_sort.hpp for general overview of the function
auto count_sort(std::span<int> a, const size_t num_threads) -> void
{
    using std::views::iota;
    using std::ranges::copy;

    // O(n) storage used to generate sorted values
    auto temp = std::vector<int>(a.size());

    // Declares the following region to be parallel over `num_threads` threads, and 
    // declares the following shared variables as well. All private variables are 
    // initialized within the for-loops
#pragma omp parallel num_threads(num_threads) default(none) shared(a, iota, temp, num_threads, copy)
    {
        // for-loop one places the sorted values into the temp array
#pragma omp for
        for (const auto i : iota(size_t{ 0 }, a.size())) {
            auto count = size_t{ 0 };

            for (const auto j : iota(size_t{ 0 }, a.size())) {
                if (a[j] < a[i]) {
                    count++;
                } else if (a[j] == a[i] && j < i) {
                    count++;
                }
            }
            temp[count] = a[i];
        }

        // once the temp array is populated, the threads evenly copy 
        // the data back into the original array
#pragma omp for
        for (const auto i : iota(size_t{ 0 }, num_threads)) {
            if (a.size() < num_threads) { continue; }

            const auto length_hint = a.size() / num_threads;
            const auto start_index = i * length_hint;
            const auto length = [&]() {
                const auto last_thread_id = num_threads - 1;
                if (i == last_thread_id) {
                    return std::dynamic_extent;
                } else {
                    return length_hint;
                }
            }();

            const auto copy_from = std::span{ temp }.subspan(start_index, length);
            auto copy_to = a.subspan(start_index, length);

            copy(copy_from, copy_to.begin());
        }
    }

    // if the size of the input was less than the number of threads, we'll just 
    // do the copying all at once instead of splitting it up over threads
    if (a.size() < num_threads) { copy(temp, a.begin()); }
}
