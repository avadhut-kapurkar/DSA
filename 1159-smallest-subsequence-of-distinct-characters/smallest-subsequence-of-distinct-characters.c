#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* smallestSubsequence(char* s) {
    static char stack[1001];
    int last[26] = {0};
    bool visited[26] = {false};

    int n = strlen(s);

    // Store last occurrence of each character
    for (int i = 0; i < n; i++) {
        last[s[i] - 'a'] = i;
    }

    int top = -1;

    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';

        if (visited[c])
            continue;

        while (top >= 0 &&
               stack[top] > s[i] &&
               last[stack[top] - 'a'] > i) {
            visited[stack[top] - 'a'] = false;
            top--;
        }

        stack[++top] = s[i];
        visited[c] = true;
    }

    stack[top + 1] = '\0';
    return stack;
}