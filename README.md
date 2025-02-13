# Count Sort w/ OpenMP | CS 6300 | Nick Waddoups

Count sort is a simple sorting algorithm with $O(N^2)$ runtime complexity _and_ 
$O(N)$ space complexity. The implementation centers around a core loop where 
for every value `i` in the input array the sorted index in the output array 
is calculated.

```cpp 
for (auto i : input) 
{
    auto sorted_index{0};
    
    for (auto j : input) 
    {
        if (i > j) sorted_index++;
    }

    // put the sorted value in the correct place in the temp 
    // storage 
    temp[sorted_index] = i;
}
```

This is not the most optimal sorting algorith, but this assignment was to learn 
how OpenMP works. The [`count_sort`](./src/count_sort.cpp) function uses OpenMP 
to parallelize the sort. 

Build the code with `make` on Unix like systems with CMake, OpenMP, and a modern 
C++20 compliant compiler. The command line application is located at "./build/cli".

