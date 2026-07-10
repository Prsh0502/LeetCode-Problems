#include <stdlib.h>

// Comparison function for qsort
int compareInts(const void* a, const void* b) {
    long long va = *(const int*)a;
    long long vb = *(const int*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (numsSize < 4) return NULL;

    // 1. Sort the array to easily handle duplicates and use two pointers
    qsort(nums, numsSize, sizeof(int), compareInts);

    // Dynamic allocation management for the result array
    int capacity = 16;
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));

    // 2. Fix the first two numbers using nested loops
    for (int i = 0; i < numsSize - 3; i++) {
        // Skip duplicates for the first number
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        for (int j = i + 1; j < numsSize - 2; j++) {
            // Skip duplicates for the second number
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            // 3. Two-pointer sweep for the remaining two numbers
            int k = j + 1;
            int l = numsSize - 1;

            while (k < l) {
                // Cast to long long to prevent integer overflow
                long long sum = (long long)nums[i] + nums[j] + nums[k] + nums[l];

                if (sum == target) {
                    // Resize results if capacity is met
                    if (*returnSize == capacity) {
                        capacity *= 2;
                        result = (int**)realloc(result, capacity * sizeof(int*));
                        *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
                    }

                    // Store the valid quadruplet
                    result[*returnSize] = (int*)malloc(4 * sizeof(int));
                    result[*returnSize][0] = nums[i];
                    result[*returnSize][1] = nums[j];
                    result[*returnSize][2] = nums[k];
                    result[*returnSize][3] = nums[l];
                    (*returnColumnSizes)[*returnSize] = 4;
                    (*returnSize)++;

                    k++;
                    l--;

                    // Skip duplicates for the third and fourth numbers
                    while (k < l && nums[k] == nums[k - 1]) k++;
                    while (k < l && nums[l] == nums[l + 1]) l--;
                } 
                else if (sum < target) {
                    k++;
                } 
                else {
                    l--;
                }
            }
        }
    }

    return result;
}