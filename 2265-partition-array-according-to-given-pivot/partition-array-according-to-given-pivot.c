/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pivotArray(int* nums, int numsSize, int pivot, int* returnSize) {
    int *result = (int *)malloc(numsSize * sizeof(int));
    int idx = 0;

    // Elements less than pivot
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < pivot) {
            result[idx++] = nums[i];
        }
    }

    // Elements equal to pivot
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == pivot) {
            result[idx++] = nums[i];
        }
    }

    // Elements greater than pivot
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > pivot) {
            result[idx++] = nums[i];
        }
    }

    *returnSize = numsSize;
    return result;
}