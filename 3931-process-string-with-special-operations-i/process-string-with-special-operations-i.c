#include <stdlib.h>
#include <string.h>

char* processStr(char* s) {
    int capacity = 1 << 20;  
    char *result = (char *)malloc(capacity);
    int len = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            result[len++] = s[i];
        }
        else if (s[i] == '*') {
            if (len > 0)
                len--;
        }
        else if (s[i] == '#') {
            for (int j = 0; j < len; j++) {
                result[len + j] = result[j];
            }
            len *= 2;
        }
        else if (s[i] == '%') {
            int l = 0, r = len - 1;
            while (l < r) {
                char temp = result[l];
                result[l] = result[r];
                result[r] = temp;
                l++;
                r--;
            }
        }
    }

    result[len] = '\0';
    return result;
}