#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int* pathsWithMaxScore(char** board, int boardSize, int* returnSize) {
    int n = boardSize;
    
    // Allocate 2D DP arrays for clarity and boundary safety
    int** dp_sum = (int**)malloc(n * sizeof(int*));
    int** dp_paths = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp_sum[i] = (int*)calloc(n, sizeof(int));
        dp_paths[i] = (int*)calloc(n, sizeof(int));
    }
    
    // Base case: Start at the bottom-right corner 'S'
    dp_paths[n - 1][n - 1] = 1;
    dp_sum[n - 1][n - 1] = 0;
    
    // Step 1: Process the bottom row (can only move left from 'S')
    for (int j = n - 2; j >= 0; j--) {
        if (board[n - 1][j] == 'X' || dp_paths[n - 1][j + 1] == 0) continue;
        int val = (board[n - 1][j] == 'E') ? 0 : (board[n - 1][j] - '0');
        dp_sum[n - 1][j] = dp_sum[n - 1][j + 1] + val;
        dp_paths[n - 1][j] = dp_paths[n - 1][j + 1];
    }
    
    // Step 2: Process the rightmost column (can only move up from 'S')
    for (int i = n - 2; i >= 0; i--) {
        if (board[i][n - 1] == 'X' || dp_paths[i + 1][n - 1] == 0) continue;
        int val = (board[i][n - 1] == 'E') ? 0 : (board[i][n - 1] - '0');
        dp_sum[i][n - 1] = dp_sum[i + 1][n - 1] + val;
        dp_paths[i][n - 1] = dp_paths[i + 1][n - 1];
    }
    
    // Step 3: Process the rest of the board from bottom to top, right to left
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            if (board[i][j] == 'X') continue;
            
            int current_val = (board[i][j] == 'E') ? 0 : (board[i][j] - '0');
            int max_prev_sum = -1;
            long long total_paths = 0;
            
            // Look Down
            if (dp_paths[i + 1][j] > 0) {
                if (dp_sum[i + 1][j] > max_prev_sum) {
                    max_prev_sum = dp_sum[i + 1][j];
                    total_paths = dp_paths[i + 1][j];
                } else if (dp_sum[i + 1][j] == max_prev_sum) {
                    total_paths = (total_paths + dp_paths[i + 1][j]) % MOD;
                }
            }
            
            // Look Right
            if (dp_paths[i][j + 1] > 0) {
                if (dp_sum[i][j + 1] > max_prev_sum) {
                    max_prev_sum = dp_sum[i][j + 1];
                    total_paths = dp_paths[i][j + 1];
                } else if (dp_sum[i][j + 1] == max_prev_sum) {
                    total_paths = (total_paths + dp_paths[i][j + 1]) % MOD;
                }
            }
            
            // Look Diagonal (Down-Right)
            if (dp_paths[i + 1][j + 1] > 0) {
                if (dp_sum[i + 1][j + 1] > max_prev_sum) {
                    max_prev_sum = dp_sum[i + 1][j + 1];
                    total_paths = dp_paths[i + 1][j + 1];
                } else if (dp_sum[i + 1][j + 1] == max_prev_sum) {
                    total_paths = (total_paths + dp_paths[i + 1][j + 1]) % MOD;
                }
            }
            
            // Update cell if it's reachable from at least one valid path
            if (max_prev_sum != -1) {
                dp_sum[i][j] = max_prev_sum + current_val;
                dp_paths[i][j] = total_paths % MOD;
            }
        }
    }
    
    // Final result destination is top-left (0,0)
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = dp_sum[0][0];
    result[1] = dp_paths[0][0];
    *returnSize = 2;
    
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(dp_sum[i]);
        free(dp_paths[i]);
    }
    free(dp_sum);
    free(dp_paths);
    
    return result;
}