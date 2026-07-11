#include <stdlib.h>
#include <string.h>

// Helper function to perform backtracking and build strings
void backtrack(char** result, int* returnSize, char* currentStr, int index, int openCount, int closeCount, int n) {
    // Base Case: When both open and close brackets reach n, a valid string is finished
    if (openCount == n && closeCount == n) {
        currentStr[index] = '\0'; // Null terminate the string
        result[*returnSize] = (char*)malloc((2 * n + 1) * sizeof(char));
        strcpy(result[*returnSize], currentStr);
        (*returnSize)++;
        return;
    }

    // Rule 1: We can always add an open parenthesis if we haven't reached the limit n
    if (openCount < n) {
        currentStr[index] = '(';
        backtrack(result, returnSize, currentStr, index + 1, openCount + 1, closeCount, n);
    }

    // Rule 2: We can only add a close parenthesis if it doesn't exceed the open ones
    if (closeCount < openCount) {
        currentStr[index] = ')';
        backtrack(result, returnSize, currentStr, index + 1, openCount, closeCount + 1, n);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    *returnSize = 0;
    
    // The total number of unique combinations is bounded by the nth Catalan number.
    // Max value for n is 8, so allocating an upper bound of 2000 pointers is more than safe.
    int maxCombinations = 2000; 
    char** result = (char**)malloc(maxCombinations * sizeof(char*));
    
    // Temporary buffer to hold the string path during recursion
    char* currentStr = (char*)malloc((2 * n + 1) * sizeof(char));
    
    // Kick off backtracking starting at index 0 with 0 open and 0 close brackets
    backtrack(result, returnSize, currentStr, 0, 0, 0, n);
    
    // Free the temporary buffer
    free(currentStr);
    
    return result;
}