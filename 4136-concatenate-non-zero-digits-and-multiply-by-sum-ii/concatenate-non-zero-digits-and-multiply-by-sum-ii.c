#include <stdlib.h>
#include <string.h>

int* sumAndMultiply(char * s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int m = strlen(s);
    long long MOD = 1000000007;

    int* C = (int*)malloc((m + 1) * sizeof(int));
    long long* S = (long long*)malloc((m + 1) * sizeof(long long));
    long long* V = (long long*)malloc((m + 1) * sizeof(long long));
    long long* P10 = (long long*)malloc((m + 1) * sizeof(long long));

    C[0] = 0;
    S[0] = 0;
    V[0] = 0;
    P10[0] = 1;

    for (int i = 1; i <= m; i++) {
        P10[i] = (P10[i - 1] * 10) % MOD;
        int d = s[i - 1] - '0';
        if (d > 0) {
            C[i] = C[i - 1] + 1;
            S[i] = S[i - 1] + d;
            V[i] = (V[i - 1] * 10 + d) % MOD;
        } else {
            C[i] = C[i - 1];
            S[i] = S[i - 1];
            V[i] = V[i - 1];
        }
    }

    int* ans = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        
        int count = C[r + 1] - C[l];
        long long sum = (S[r + 1] - S[l]) % MOD;
        
        long long sub_val = (V[l] * P10[count]) % MOD;
        long long x = (V[r + 1] - sub_val + MOD) % MOD;
        
        ans[i] = (x * sum) % MOD;
    }

    free(C);
    free(S);
    free(V);
    free(P10);

    return ans;
}