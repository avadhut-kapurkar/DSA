#define MOD 1000000007

void multiply(long long A[150][150], long long B[150][150], int S) {
    long long C[150][150];
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            C[i][j] = 0;
        }
    }
    for (int i = 0; i < S; i++) {
        for (int k = 0; k < S; k++) {
            if (!A[i][k]) continue;
            for (int j = 0; j < S; j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            A[i][j] = C[i][j];
        }
    }
}

void power(long long A[150][150], int p, int S) {
    long long res[150][150];
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            res[i][j] = (i == j) ? 1 : 0;
        }
    }
    while (p > 0) {
        if (p % 2 == 1) multiply(res, A, S);
        multiply(A, A, S);
        p /= 2;
    }
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            A[i][j] = res[i][j];
        }
    }
}

int zigZagArrays(int n, int l, int r) {
    int k = r - l + 1;
    int S = 2 * k;
    long long V[150];
    
    for (int i = 0; i < 150; i++) {
        V[i] = 0;
    }
    for (int i = 0; i < k; i++) {
        V[i] = i; 
        V[i + k] = k - 1 - i;
    }
    
    long long M[150][150];
    for (int i = 0; i < 150; i++) {
        for (int j = 0; j < 150; j++) {
            M[i][j] = 0;
        }
    }
    
    for (int y = 0; y < k; y++) {
        for (int x = y + 1; x < k; x++) {
            M[y + k][x] = 1;
        }
    }
    for (int y = 0; y < k; y++) {
        for (int x = 0; x < y; x++) {
            M[y][x + k] = 1;
        }
    }
    
    power(M, n - 2, S);
    
    long long ans = 0;
    for (int i = 0; i < S; i++) {
        long long sum = 0;
        for (int j = 0; j < S; j++) {
            sum = (sum + M[i][j] * V[j]) % MOD;
        }
        ans = (ans + sum) % MOD;
    }
    
    return (int)ans;
}