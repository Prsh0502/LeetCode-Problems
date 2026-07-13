#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int* sequentialDigits(int low, int high, int* returnSize) {
    // There are only 36 possible sequential numbers total across all lengths.
    int* result = (int*)malloc(40 * sizeof(int));
    *returnSize = 0;
    
    char digits[] = "123456789";
    
    // Determine digit lengths for bounds
    char lowStr[12], highStr[12];
    sprintf(lowStr, "%d", low);
    sprintf(highStr, "%d", high);
    int minLen = strlen(lowStr);
    int maxLen = strlen(highStr);
    
    // Outer loop controls the length of the sequential numbers
    for (int len = minLen; len <= maxLen; len++) {
        // Inner loop slides across the "123456789" pool
        for (int start = 0; start + len <= 9; start++) {
            // Construct the integer from the current window
            int num = 0;
            for (int i = start; i < start + len; i++) {
                num = num * 10 + (digits[i] - '0');
            }
            
            // Check if it fits the problem criteria
            if (num >= low && num <= high) {
                result[(*returnSize)++] = num;
            }
        }
    }
    
    return result;
}