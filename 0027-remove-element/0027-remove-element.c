int removeElement(int* nums, int numsSize, int val) {
    int k = 0; // Pointer to track the position of valid elements
    
    for (int i = 0; i < numsSize; i++) {
        // If the current element is not the value to remove
        if (nums[i] != val) {
            nums[k] = nums[i]; // Move it to the 'k'-th index
            k++;               // Increment the count of valid elements
        }
    }
    
    return k; // k is the number of elements not equal to val
}