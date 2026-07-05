#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* simplifyPath(char* path) {
    int len = strlen(path);
    
    // Stack to store valid directory names
    // In the worst case (e.g., "/a/b/c"), there can be at most len/2 directories
    char** stack = (char**)malloc(len * sizeof(char*));
    int top = 0;
    
    // Use strtok to split the path string by the '/' delimiter
    char* token = strtok(path, "/");
    
    while (token != NULL) {
        if (strcmp(token, ".") == 0 || strlen(token) == 0) {
            // "Current directory" or empty token from duplicate slashes; do nothing
        } else if (strcmp(token, "..") == 0) {
            // "Parent directory"; pop from stack if it's not empty
            if (top > 0) {
                top--;
            }
        } else {
            // Valid directory name; push onto stack
            stack[top++] = token;
        }
        token = strtok(NULL, "/");
    }
    
    // Construct the canonical path result string
    // Allocate memory for the worst case (original length + 1 for null terminator)
    char* result = (char*)malloc((len + 2) * sizeof(char));
    result[0] = '\0';
    
    if (top == 0) {
        // If the stack is empty, the path defaults to root "/"
        strcpy(result, "/");
    } else {
        // Reconstruct the path by joining directory names with '/'
        for (int i = 0; i < top; i++) {
            strcat(result, "/");
            strcat(result, stack[i]);
        }
    }
    
    free(stack);
    return result;
}