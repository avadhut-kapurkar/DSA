#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = -1;
    result[1] = -1;
    *returnSize = 2;

    if (numsSize == 0) {
        return result;
    }

    // 1. Binary search for the first occurrence (leftmost)
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            result[0] = mid;
            right = mid - 1; // Target found, but keep searching to the left
        }
    }

    // If the target wasn't found at all, we can return early
    if (result[0] == -1) {
        return result;
    }

    // 2. Binary search for the last occurrence (rightmost)
    left = 0; 
    right = numsSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            result[1] = mid;
            left = mid + 1; // Target found, but keep searching to the right
        }
    }

    return result;
}