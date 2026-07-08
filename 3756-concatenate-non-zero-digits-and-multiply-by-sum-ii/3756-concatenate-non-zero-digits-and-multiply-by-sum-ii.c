#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

// Function to calculate (base^exp) % MOD
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Function to calculate modular inverse using Fermat's Little Theorem
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

/**
 * Note: The returned array must be malloced, assume caller frees it.
 */
int* sumAndMultiply(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int m = strlen(s);
    
    // Allocate prefix arrays
    int* C = (int*)malloc((m + 1) * sizeof(int));      // Count of non-zero digits
    long long* S = (long long*)malloc((m + 1) * sizeof(long long)); // Sum of digits
    long long* P = (long long*)malloc((m + 1) * sizeof(long long)); // Mod-inv scaled prefix sum for x
    
    // Precompute powers of 10 and its inverse
    long long* pow10 = (long long*)malloc((m + 1) * sizeof(long long));
    long long* invPow10 = (long long*)malloc((m + 1) * sizeof(long long));
    
    long long inv10 = modInverse(10);
    pow10[0] = 1;
    invPow10[0] = 1;
    for (int i = 1; i <= m; i++) {
        pow10[i] = (pow10[i - 1] * 10) % MOD;
        invPow10[i] = (invPow10[i - 1] * inv10) % MOD;
    }
    
    C[0] = 0;
    S[0] = 0;
    P[0] = 0;
    
    // Fill the prefix arrays (1-indexed for convenience)
    for (int i = 0; i < m; i++) {
        int d = s[i] - '0';
        if (d > 0) {
            C[i + 1] = C[i] + 1;
            S[i + 1] = S[i] + d;
            long long term = (d * invPow10[C[i + 1]]) % MOD;
            P[i + 1] = (P[i] + term) % MOD;
        } else {
            C[i + 1] = C[i];
            S[i + 1] = S[i];
            P[i + 1] = P[i];
        }
    }
    
    // Process queries
    int* answer = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        
        int L = l; 
        int R = r + 1;
        
        // 1. Compute the sum of digits in the range
        long long current_sum = S[R] - S[L];
        
        // 2. Compute x modulo 10^9 + 7
        long long diff = (P[R] - P[L] + MOD) % MOD;
        long long x = (diff * pow10[C[R]]) % MOD;
        
        // 3. Compute final query answer
        long long ans = (x * current_sum) % MOD;
        answer[i] = (int)ans;
    }
    
    // Clean up temporary allocations
    free(C);
    free(S);
    free(P);
    free(pow10);
    free(invPow10);
    
    return answer;
}