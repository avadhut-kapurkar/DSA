/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sequentialDigits(int low, int high, int* returnSize) {
    int *res = (int *)malloc(40 * sizeof(int));
    *returnSize = 0;
    char s[] = "123456789";

    for (int len = 2; len <= 9; len++) {
        for (int i = 0; i + len <= 9; i++) {
            int num = 0;
            for (int j = 0; j < len; j++) {
                num = num * 10 + (s[i + j] - '0');
            }
            if (num >= low && num <= high) {
                res[(*returnSize)++] = num;
            }
        }
    }

    return res;
}