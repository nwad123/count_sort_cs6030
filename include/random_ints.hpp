#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

/// Wrapper class around ::rand() from `cstdlib` so that we can use 
/// std::shuffle with ::rand()
struct Rand
{
    using utype = uint32_t;
    using result_type = utype; 

    inline auto operator()() -> utype { return static_cast<utype>(::rand()); }
    static constexpr auto max() -> utype
    {
        return std::max(std::numeric_limits<utype>::max(), static_cast<utype>(RAND_MAX));
    }
    static constexpr auto min() -> utype { return 0; }
};
static_assert(std::uniform_random_bit_generator<Rand>);

/// Returns a vector of ints ranging from 1 to `size` that are randomly shuffled
template<size_t SEED = 100>
[[nodiscard]]
auto random_ints(const size_t size) -> std::vector<int>
{
    ::srand(SEED);
    std::vector ints(size, 0);
    std::iota(ints.begin(), ints.end(), 1);
    std::shuffle(ints.begin(), ints.end(), Rand{});

    return ints;
}
