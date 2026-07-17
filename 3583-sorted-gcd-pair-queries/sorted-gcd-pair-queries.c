#include <stdlib.h>

#define MAXV 50000

static int freq[MAXV + 1];
static int cntDiv[MAXV + 1];
static long long exact[MAXV + 1];
static long long prefix[MAXV + 1];

int cmpLongLong(const void *a, const void *b) {
    long long x = *(long long *)a;
    long long y = *(long long *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int* gcdValues(int* nums, int numsSize, long long* queries, int queriesSize, int* returnSize) {

    for (int i = 0; i <= MAXV; i++) {
        freq[i] = 0;
        cntDiv[i] = 0;
        exact[i] = 0;
        prefix[i] = 0;
    }

    int maxNum = 0;

    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
        if (nums[i] > maxNum)
            maxNum = nums[i];
    }

    // Count numbers divisible by each d
    for (int d = 1; d <= maxNum; d++) {
        for (int j = d; j <= maxNum; j += d)
            cntDiv[d] += freq[j];
    }

    // Inclusion-Exclusion to count pairs with exact gcd=d
    for (int d = maxNum; d >= 1; d--) {
        long long c = cntDiv[d];
        exact[d] = c * (c - 1) / 2;

        for (int m = d + d; m <= maxNum; m += d)
            exact[d] -= exact[m];
    }

    // Prefix counts
    for (int i = 1; i <= maxNum; i++)
        prefix[i] = prefix[i - 1] + exact[i];

    int *ans = (int *)malloc(sizeof(int) * queriesSize);

    for (int i = 0; i < queriesSize; i++) {

        long long k = queries[i] + 1;

        int l = 1, r = maxNum;

        while (l < r) {
            int mid = (l + r) / 2;

            if (prefix[mid] >= k)
                r = mid;
            else
                l = mid + 1;
        }

        ans[i] = l;
    }

    *returnSize = queriesSize;
    return ans;
}