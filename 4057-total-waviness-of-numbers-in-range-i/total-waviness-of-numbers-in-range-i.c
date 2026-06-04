int getWaviness(int num) {
    char s[12];
    sprintf(s, "%d", num);

    int len = strlen(s);

    if (len < 3)
        return 0;

    int waviness = 0;

    for (int i = 1; i < len - 1; i++) {
        int prev = s[i - 1] - '0';
        int curr = s[i] - '0';
        int next = s[i + 1] - '0';

        // Peak
        if (curr > prev && curr > next)
            waviness++;

        // Valley
        else if (curr < prev && curr < next)
            waviness++;
    }

    return waviness;
}

long long totalWaviness(int num1, int num2) {
    long long ans = 0;

    for (int num = num1; num <= num2; num++) {
        ans += getWaviness(num);
    }

    return ans;
}