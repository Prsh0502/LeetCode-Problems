#include <string.h>

int numOfStrings(char** patterns, int patternsSize, char* word) {
    int count = 0;
    
    // Loop through each pattern in the array
    for (int i = 0; i < patternsSize; i++) {
        // strstr returns non-NULL if patterns[i] is found inside word
        if (strstr(word, patterns[i]) != NULL) {
            count++;
        }
    }
    
    return count;
}