#include "count_sort_reference.hpp"
#include <cstdlib>
#include <cstring>

void count_sort_reference(int a[], int n)
{
    int i, j, count;
    int *temp = (int *)::malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        temp[count] = a[i];
    }

    ::memcpy(a, temp, n * sizeof(int));
    free(temp);
}
