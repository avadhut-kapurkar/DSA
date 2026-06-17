#include <stdlib.h>
#include <string.h>

char processStr(char* s, long long k) {
    int n = strlen(s);
    long long *len = (long long *)malloc((n + 1) * sizeof(long long));
    len[0] = 0;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c >= 'a' && c <= 'z') {
            len[i + 1] = len[i] + 1;
        } else if (c == '*') {
            len[i + 1] = (len[i] > 0) ? len[i] - 1 : 0;
        } else if (c == '#') {
            len[i + 1] = len[i] * 2;
        } else {
            len[i + 1] = len[i];
        }
    }

    if (k >= len[n]) {
        free(len);
        return '.';
    }

    for (int i = n - 1; i >= 0; i--) {
        char c = s[i];
        long long prev = len[i];
        if (c >= 'a' && c <= 'z') {
            if (k == prev) {
                free(len);
                return c;
            }
        } else if (c == '#') {
            if (k >= prev) k -= prev;
        } else if (c == '%') {
            k = prev - 1 - k;
        }
    }

    free(len);
    return '.';
}