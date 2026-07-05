#include <stdio.h>
#include <string.h>

int maxNumberOfBalloons(char* text) {
    // Array to store frequencies of 'b', 'a', 'l', 'o', 'n'
    // Index mapping: 0='b', 1='a', 2='l', 3='o', 4='n'
    int counts[5] = {0};
    
    // Step 1: Count relevant characters in the text
    for (int i = 0; text[i] != '\0'; i++) {
        switch (text[i]) {
            case 'b': counts[0]++; break;
            case 'a': counts[1]++; break;
            case 'l': counts[2]++; break;
            case 'o': counts[3]++; break;
            case 'n': counts[4]++; break;
            default:  break; // Ignore all other characters
        }
    }
    
    // Step 2: Account for letters that appear multiple times per word
    counts[2] /= 2; // 'l' requires 2 instances
    counts[3] /= 2; // 'o' requires 2 instances
    
    // Step 3: Find the limiting character (the minimum count)
    int max_words = counts[0];
    for (int i = 1; i < 5; i++) {
        if (counts[i] < max_words) {
            max_words = counts[i];
        }
    }
    
    return max_words;
}