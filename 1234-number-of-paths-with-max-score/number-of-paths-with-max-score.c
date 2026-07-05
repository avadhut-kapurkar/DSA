#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 1000000007
#define INF -1

int max(int a, int b) {
    return a > b ? a : b;
}

int* pathsWithMaxScore(char ** board, int boardSize, int* returnSize) {
    int n = boardSize;

    int (*dpScore)[105] = malloc(sizeof(int) * 105 * 105);
    int (*dpWays)[105]  = malloc(sizeof(int) * 105 * 105);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dpScore[i][j] = INF;
            dpWays[i][j] = 0;
        }
    }

    // Start from S (bottom-right)
    dpScore[n-1][n-1] = 0;
    dpWays[n-1][n-1] = 1;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {

            if (board[i][j] == 'X') continue;
            if (i == n - 1 && j == n - 1) continue;

            int best = -1;
            long ways = 0;

            // down
            if (i + 1 < n && dpWays[i + 1][j]) {
                if (dpScore[i + 1][j] > best) {
                    best = dpScore[i + 1][j];
                    ways = dpWays[i + 1][j];
                } else if (dpScore[i + 1][j] == best) {
                    ways = (ways + dpWays[i + 1][j]) % MOD;
                }
            }

            // right
            if (j + 1 < n && dpWays[i][j + 1]) {
                if (dpScore[i][j + 1] > best) {
                    best = dpScore[i][j + 1];
                    ways = dpWays[i][j + 1];
                } else if (dpScore[i][j + 1] == best) {
                    ways = (ways + dpWays[i][j + 1]) % MOD;
                }
            }

            // diagonal
            if (i + 1 < n && j + 1 < n && dpWays[i + 1][j + 1]) {
                if (dpScore[i + 1][j + 1] > best) {
                    best = dpScore[i + 1][j + 1];
                    ways = dpWays[i + 1][j + 1];
                } else if (dpScore[i + 1][j + 1] == best) {
                    ways = (ways + dpWays[i + 1][j + 1]) % MOD;
                }
            }

            if (ways == 0) continue;

            int val = 0;
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                val = board[i][j] - '0';
            }

            dpScore[i][j] = best + val;
            dpWays[i][j] = ways % MOD;
        }
    }

    int* ans = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;

    if (dpWays[0][0] == 0) {
        ans[0] = 0;
        ans[1] = 0;
    } else {
        ans[0] = dpScore[0][0];
        ans[1] = dpWays[0][0];
    }

    return ans;
}