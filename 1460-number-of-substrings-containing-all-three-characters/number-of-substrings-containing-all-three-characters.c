long long numberOfSubstrings(char *s) {
    int count[3] = {0};
    int left = 0;
    long long ans = 0;

    for (int right = 0; s[right] != '\0'; right++) {
        count[s[right] - 'a']++;

        while (count[0] > 0 && count[1] > 0 && count[2] > 0) {
            ans += strlen(s) - right;
            count[s[left] - 'a']--;
            left++;
        }
    }

    return ans;
}