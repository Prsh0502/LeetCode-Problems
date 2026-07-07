#include <stdio.h>
#include <stdlib.h>

long long sumAndMultiply(int n) {
    long long total_sum = 0;
    long long reversed_x = 0;
    
    // Step 1: Extract digits from right to left
    while (n > 0) {
        int digit = n % 10;
        total_sum += digit; 
        
        if (digit != 0) {
            reversed_x = reversed_x * 10 + digit;
        }
        n /= 10;
    }
    
    // Step 2: Reverse the non-zero concatenation to restore original left-to-right order
    long long x = 0;
    while (reversed_x > 0) {
        x = x * 10 + (reversed_x % 10);
        reversed_x /= 10;
    }
    
    // Step 3: Return the final product
    return x * total_sum;
}