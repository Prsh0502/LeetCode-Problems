#include <stdio.h>
#include <stdlib.h>

// Custom comparator function for qsort
int compareIntervals(const void* a, const void* b) {
    int* intervalA = *(int**)a;
    int* intervalB = *(int**)b;
    
    // If start points are equal, sort by end points in descending order
    if (intervalA[0] == intervalB[0]) {
        return intervalB[1] - intervalA[1];
    }
    // Otherwise, sort by start points in ascending order
    return intervalA[0] - intervalB[0];
}

int removeCoveredIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    if (intervalsSize == 0) return 0;
    
    // Step 1: Sort the intervals using our custom comparator
    qsort(intervals, intervalsSize, sizeof(int*), compareIntervals);
    
    int remaining_count = 0;
    int max_end = 0;
    
    // Step 2: Traverse through the intervals and count non-covered ones
    for (int i = 0; i < intervalsSize; i++) {
        int current_end = intervals[i][1];
        
        // If the current end point extends past the maximum end point seen so far,
        // it cannot be completely covered by any previous interval.
        if (current_end > max_end) {
            remaining_count++;
            max_end = current_end; // Update the boundary
        }
    }
    
    return remaining_count;
}