#include <stdlib.h>
#include <stdbool.h>

bool* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // 1. Group components based on consecutive differences.
    // Memory footprint is reduced to just a single integer array of size n.
    int* group = (int*)malloc(n * sizeof(int));
    
    int currentGroup = 0;
    group[0] = currentGroup;
    
    for (int i = 1; i < n; i++) {
        // Since nums is sorted, nums[i] >= nums[i-1]
        if (nums[i] - nums[i-1] > maxDiff) {
            currentGroup++; // Start a new connected component
        }
        group[i] = currentGroup;
    }
    
    // 2. Process each query in O(1) time
    bool* result = (bool*)malloc(queriesSize * sizeof(bool));
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];
        
        // If they are in the same contiguous group, a path exists
        result[i] = (group[u] == group[v]);
    }
    
    // Clean up temporary group array memory
    free(group);
    
    return result;
}