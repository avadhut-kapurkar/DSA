#include <stdio.h>
#include <stdlib.h>

// Function to add a value to the Fenwick Tree (BIT)
void add(int* bit, int n, int idx, int val) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += val;
    }
}

// Function to query the sum up to a specific index in the Fenwick Tree
int query(int* bit, int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

// Renamed to countMajoritySubarrays to match the platform's expected signature
long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    long long count = 0;
    int curr_sum = 0;
    
    // The prefix sum can range from -numsSize to +numsSize.
    // We need an offset to make all indices strictly positive for the Fenwick Tree.
    // Minimum possible sum is -numsSize. With an offset of numsSize + 2, 
    // the minimum index becomes 2. 
    int offset = numsSize + 2;
    int max_bit_size = 2 * numsSize + 3;
    
    // Allocate memory for the Fenwick tree and initialize to 0
    int* bit = (int*)calloc(max_bit_size, sizeof(int));
    
    // Add the initial prefix sum of 0 (conceptually before the first element)
    add(bit, max_bit_size - 1, 0 + offset, 1);
    
    for (int i = 0; i < numsSize; i++) {
        // Transform the array on the fly
        if (nums[i] == target) {
            curr_sum += 1;
        } else {
            curr_sum -= 1;
        }
        
        // We want to find how many prefix sums seen so far are strictly LESS than curr_sum.
        // Therefore, we query up to (curr_sum - 1) + offset.
        count += query(bit, curr_sum - 1 + offset);
        
        // Add the current prefix sum to our Fenwick Tree
        add(bit, max_bit_size - 1, curr_sum + offset, 1);
    }
    
    free(bit);
    return count;
}