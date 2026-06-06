#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* leftRightDifference(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;

    int *answer = (int *)malloc(numsSize * sizeof(int));

    int totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }

    int leftSum = 0;

    for (int i = 0; i < numsSize; i++) {
        int rightSum = totalSum - leftSum - nums[i];
        answer[i] = abs(leftSum - rightSum);
        leftSum += nums[i];
    }

    return answer;
}

/*Example Usage
int main() {
    int nums[] = {10, 4, 8, 3};
    int n = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    int *result = leftRightDifference(nums, n, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}
*/