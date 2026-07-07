long long sumAndMultiply(int n) {
    if (n == 0)
        return 0;

    int d[10], c = 0;

    while (n > 0) {
        d[c++] = n % 10;
        n /= 10;
    }

    long long x = 0;
    int sum = 0;

    for (int i = c - 1; i >= 0; i--) {
        if (d[i] != 0) {
            x = x * 10 + d[i];
            sum += d[i];
        }
    }

    return x * sum;
}