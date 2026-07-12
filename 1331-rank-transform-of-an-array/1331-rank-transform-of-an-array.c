#include <stdlib.h>

// Comparison function for qsort
int compareInts(const void* a, const void* b) {
    int valA = *(const int*)a;
    int valB = *(const int*)b;
    if (valA < valB) return -1;
    if (valA > valB) return 1;
    return 0;
}

// Binary search to find the index of target in the unique sorted array
int binarySearch(int* arr, int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int* arrayRankTransform(int* arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;
    
    // Handle empty array edge case
    if (arrSize == 0) {
        return NULL;
    }

    // 1. Create a duplicate copy of the array and sort it
    int* sortedUnique = (int*)malloc(arrSize * sizeof(int));
    for (int i = 0; i < arrSize; i++) {
        sortedUnique[i] = arr[i];
    }
    qsort(sortedUnique, arrSize, sizeof(int), compareInts);

    // 2. Remove duplicate values in-place
    int uniqueSize = 0;
    for (int i = 0; i < arrSize; i++) {
        if (uniqueSize == 0 || sortedUnique[i] != sortedUnique[uniqueSize - 1]) {
            sortedUnique[uniqueSize++] = sortedUnique[i];
        }
    }

    // 3. Map original array values to their ranks using binary search
    int* result = (int*)malloc(arrSize * sizeof(int));
    for (int i = 0; i < arrSize; i++) {
        int idx = binarySearch(sortedUnique, uniqueSize, arr[i]);
        result[i] = idx + 1; // Rank starts from 1
    }

    // Free the temporary helper array
    free(sortedUnique);

    return result;
}