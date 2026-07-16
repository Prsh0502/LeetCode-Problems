#include <stdlib.h>

// Helper function to calculate the Greatest Common Divisor (GCD)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Comparison function for qsort
int compareInts(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

long long gcdSum(int* nums, int numsSize) {
    int* prefixGcd = (int*)malloc(numsSize * sizeof(int));
    int mx = 0;
    
    // 1. Build the prefixGcd array matching maximum track criteria
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > mx) {
            mx = nums[i];
        }
        prefixGcd[i] = (int)gcd(nums[i], mx);
    }
    
    // 2. Sort the generated results array
    qsort(prefixGcd, numsSize, sizeof(int), compareInts);
    
    // 3. Pair smallest and largest bounds using two pointers
    long long totalGcdSum = 0;
    for (int i = 0; i < numsSize / 2; i++) {
        totalGcdSum += gcd(prefixGcd[i], prefixGcd[numsSize - 1 - i]);
    }
    
    // Free dynamic allocation memory
    free(prefixGcd);
    
    return totalGcdSum;
}