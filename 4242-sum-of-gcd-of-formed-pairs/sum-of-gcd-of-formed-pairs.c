#include <stdlib.h>

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

long long gcdSum(int* nums, int numsSize) {
    int *prefixGcd = (int *)malloc(numsSize * sizeof(int));

    int mx = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > mx)
            mx = nums[i];
        prefixGcd[i] = gcd(nums[i], mx);
    }

    qsort(prefixGcd, numsSize, sizeof(int), cmp);

    long long ans = 0;
    int l = 0, r = numsSize - 1;

    while (l < r) {
        ans += gcd(prefixGcd[l], prefixGcd[r]);
        l++;
        r--;
    }

    free(prefixGcd);
    return ans;
}