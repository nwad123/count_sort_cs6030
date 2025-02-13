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

## Answers To Questions 

1. `count` and `j` should be marked as `private` as they are local to each loop. In my
   code we get around this issue by just using local variables inside the loop. `temp`
   and `a` will need to be `shared`, as every thread should be able to access them.
2. If `memcpy()` is not parallelizable I would write my own simple implementation of
   `memcpy()` that is parallelizable. Here's a rough draft of what it would look like:

   ```cpp
   // thread safe memcpy
   void memcpy_ts(/*out*/ void *dest, /*in*/ const void *src, /*in*/ const size_t num_bytes)
   {
       using byte = uint8_t;
       byte *dest_b = (byte*)dest;
       const byte *src_b = (const byte*)src;

       for (size_t i = 0; i < num_bytes; i++)
       {
           dest_b[i] = src_b[i];
       }
   }
   ```
