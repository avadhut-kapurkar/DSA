#include <stdlib.h>

#define MAXV 200
#define MOD 1000000007

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int subsequencePairCount(int* nums, int numsSize) {
    static long long dp[MAXV + 1][MAXV + 1];
    static long long ndp[MAXV + 1][MAXV + 1];

    for (int i = 0; i <= MAXV; i++)
        for (int j = 0; j <= MAXV; j++)
            dp[i][j] = 0;

    dp[0][0] = 1;

    for (int idx = 0; idx < numsSize; idx++) {
        int x = nums[idx];

        for (int i = 0; i <= MAXV; i++)
            for (int j = 0; j <= MAXV; j++)
                ndp[i][j] = dp[i][j];

        for (int g1 = 0; g1 <= MAXV; g1++) {
            for (int g2 = 0; g2 <= MAXV; g2++) {
                long long cur = dp[g1][g2];
                if (cur == 0) continue;

                int ng1 = (g1 == 0) ? x : gcd(g1, x);
                ndp[ng1][g2] = (ndp[ng1][g2] + cur) % MOD;

                int ng2 = (g2 == 0) ? x : gcd(g2, x);
                ndp[g1][ng2] = (ndp[g1][ng2] + cur) % MOD;
            }
        }

        for (int i = 0; i <= MAXV; i++)
            for (int j = 0; j <= MAXV; j++)
                dp[i][j] = ndp[i][j];
    }

    long long ans = 0;
    for (int g = 1; g <= MAXV; g++)
        ans = (ans + dp[g][g]) % MOD;

    return (int)ans;
}