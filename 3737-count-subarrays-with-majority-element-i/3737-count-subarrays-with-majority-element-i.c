#include <stdio.h>

int countMajoritySubarrays(int* nums, int numsSize, int target) {
    int total_subarrays = 0;
    
    // Traverse through each possible starting element of the subarray
    for (int i = 0; i < numsSize; i++) {
        int target_count = 0;
        
        // Expand the current subarray window from index i to j
        for (int j = i; j < numsSize; j++) {
            if (nums[j] == target) {
                target_count++;
            }
            
            int current_length = j - i + 1;
            
            // The target is the majority element if it appears strictly more than half the time
            if (target_count > current_length / 2) {
                total_subarrays++;
            }
        }
    }
    
    return total_subarrays;
}