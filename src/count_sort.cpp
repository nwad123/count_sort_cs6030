#include "count_sort.hpp"
#include <ranges>
#ifdef _OPENMP 
#include <omp.h>
#endif

auto count_sort_cpp_(std::span<int> a, const size_t num_threads) -> void
{
    using std::views::iota;
    using std::ranges::copy;

    auto temp = std::vector<int>(a.size());

#pragma omp parallel num_threads(num_threads) default(none) shared(a, iota, temp, num_threads, copy)
    {
#pragma omp for
        for (const auto i : iota(size_t{ 0 }, size_t{ a.size() })) {
            auto count = size_t{ 0 };

            for (const auto j : iota(size_t{ 0 }, size_t{ a.size() })) {
                if (a[j] < a[i]) {
                    count++;
                } else if (a[j] == a[i] && j < i) {
                    count++;
                }
            }
            temp[count] = a[i];
        }

#pragma omp for
        for (const auto i : iota(size_t{ 0 }, num_threads)) {
            if (a.size() < num_threads) { continue; }

            const auto start_index = i * a.size();
            const auto length = [&]() {
                const auto last_thread_id = num_threads - 1;
                if (i == last_thread_id) {
                    return std::dynamic_extent;
                } else {
                    return a.size() / num_threads;
                }
            }();

            const auto copy_from = std::span{ temp }.subspan(start_index, length);
            auto copy_to = a.subspan(start_index, length);

            copy(copy_from, copy_to.begin());
        }
    }

    if (a.size() < num_threads) { copy(temp, a.begin()); }
}
