#include <string.h>

bool repeatedSubstringPattern(char* s) {
    int n = strlen(s);

    // Try every possible substring length
    for (int len = 1; len <= n / 2; len++) {

        // n must be divisible by len
        if (n % len != 0)
            continue;

        bool match = true;

        // Compare the whole string with repeated substring
        for (int i = 0; i < n; i++) {
            if (s[i] != s[i % len]) {
                match = false;
                break;
            }
        }

        if (match)
            return true;
    }

    return false;
}