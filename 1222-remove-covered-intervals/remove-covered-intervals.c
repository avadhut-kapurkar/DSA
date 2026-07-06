#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int *x = *(int **)a;
    int *y = *(int **)b;

    if (x[0] == y[0])
        return y[1] - x[1];  // end descending
    return x[0] - y[0];      // start ascending
}

int removeCoveredIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    qsort(intervals, intervalsSize, sizeof(int *), compare);

    int remaining = 0;
    int maxEnd = 0;

    for (int i = 0; i < intervalsSize; i++) {
        if (intervals[i][1] > maxEnd) {
            remaining++;
            maxEnd = intervals[i][1];
        }
    }

    return remaining;
}