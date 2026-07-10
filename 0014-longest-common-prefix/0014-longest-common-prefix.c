#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) {
        char* empty = (char*)malloc(sizeof(char));
        empty[0] = '\0';
        return empty;
    }

    // 1. Initialize the prefix with the first string
    // We create a dynamically allocated copy because we need to modify it or return it safely
    char* prefix = (char*)malloc((strlen(strs[0]) + 1) * sizeof(char));
    strcpy(prefix, strs[0]);

    // 2. Scan through the rest of the strings
    for (int i = 1; i < strsSize; i++) {
        // While strs[i] does not start with the current prefix
        while (strncmp(strs[i], prefix, strlen(prefix)) != 0) {
            // Shorten the prefix by removing its last character
            int len = strlen(prefix);
            if (len == 0) {
                return prefix; // Prefix became empty, no common prefix exists
            }
            prefix[len - 1] = '\0';
        }
    }

    return prefix;
}