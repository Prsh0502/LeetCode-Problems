#include <stdlib.h>
#include <math.h>

int* leftRightDifference(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* answer = (int*)malloc(numsSize * sizeof(int));
    
    int leftSum = 0;
    int rightSum = 0;
    
    // 1. Calculate the total sum of the array (initial rightSum)
    for (int i = 0; i < numsSize; i++) {
        rightSum += nums[i];
    }
    
    // 2. Compute the differences using a running sum technique
    for (int i = 0; i < numsSize; i++) {
        // Exclude the current element from the right sum
        rightSum -= nums[i];
        
        // Compute absolute difference
        answer[i] = abs(leftSum - rightSum);
        
        // Include the current element in the left sum for the next iteration
        leftSum += nums[i];
    }
    
    return answer;
}