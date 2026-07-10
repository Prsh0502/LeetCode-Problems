#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_LOG 18

// Comparison function for qsort
int compareInts(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Helper binary search function to find the furthest index in U such that U[mid] <= target
int findFurthest(int* U, int m, int target) {
    int low = 0, high = m - 1;
    int ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (U[mid] <= target) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // 1. Find all unique values and sort them
    int* U = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        U[i] = nums[i];
    }
    qsort(U, n, sizeof(int), compareInts);
    
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (m == 0 || U[i] != U[m - 1]) {
            U[m++] = U[i];
        }
    }
    
    // Since nums[i] <= 10^5, we can use a direct lookup array to find a value's index in U
    int maxVal = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }
    int* valToIdx = (int*)malloc((maxVal + 1) * sizeof(int));
    for (int i = 0; i < m; i++) {
        valToIdx[U[i]] = i;
    }
    
    // 2. Initialize the binary lifting table over unique values
    int** up = (int**)malloc(MAX_LOG * sizeof(int*));
    for (int k = 0; k < MAX_LOG; k++) {
        up[k] = (int*)malloc(m * sizeof(int));
    }
    
    for (int i = 0; i < m; i++) {
        up[0][i] = findFurthest(U, m, U[i] + maxDiff);
    }
    
    for (int k = 1; k < MAX_LOG; k++) {
        for (int i = 0; i < m; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }
    
    // 3. Process the queries
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];
        
        if (u == v) {
            result[i] = 0;
            continue;
        }
        
        int valA = nums[u];
        int valB = nums[v];
        
        // Direct edge case
        if (abs(valA - valB) <= maxDiff) {
            result[i] = 1;
            continue;
        }
        
        // Ensure valA is smaller to lift forward towards valB
        if (valA > valB) {
            int temp = valA;
            valA = valB;
            valB = temp;
        }
        
        int curr = valToIdx[valA];
        int targetIdx = valToIdx[valB];
        int steps = 0;
        
        for (int k = MAX_LOG - 1; k >= 0; k--) {
            if (up[k][curr] < targetIdx) {
                curr = up[k][curr];
                steps += (1 << k);
            }
        }
        
        // Take one final jump to see if we can reach or pass targetIdx
        if (up[0][curr] >= targetIdx) {
            result[i] = steps + 1;
        } else {
            result[i] = -1; // Unreachable
        }
    }
    
    // Clean up memory
    for (int k = 0; k < MAX_LOG; k++) {
        free(up[k]);
    }
    free(up);
    free(U);
    free(valToIdx);
    
    return result;
}