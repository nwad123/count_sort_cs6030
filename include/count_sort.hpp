#pragma once

#include <span>

/// My implementation of count sort 
///
/// `a` This is the array that is to be sorted in place 
/// `num_threads` Is the number of threads to use
///
/// Count sort uses O(n) storage and sorts the input `a` in place.
auto count_sort(/*inout*/ std::span<int> a, /*in*/ const size_t num_threads) -> void;
