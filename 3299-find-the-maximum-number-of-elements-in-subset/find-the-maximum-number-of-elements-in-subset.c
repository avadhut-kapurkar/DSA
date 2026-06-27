#include <stdlib.h>

struct Element {
    long long val;
    int count;
};

// Helper function must be OUTSIDE maximumLength
int compare(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

// Helper function must be OUTSIDE maximumLength
int get_count(struct Element *freqs, int size, long long target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (freqs[mid].val == target) {
            return freqs[mid].count;
        }
        if (freqs[mid].val < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0;
}

// Main function
int maximumLength(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compare);
    
    struct Element* freqs = (struct Element*)malloc(numsSize * sizeof(struct Element));
    int unique_count = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (unique_count == 0 || freqs[unique_count - 1].val != nums[i]) {
            freqs[unique_count].val = nums[i];
            freqs[unique_count].count = 1;
            unique_count++;
        } else {
            freqs[unique_count - 1].count++;
        }
    }
    
    int max_len = 1;
    
    for (int i = 0; i < unique_count; i++) {
        long long curr = freqs[i].val;
        
        // Edge case for 1: it powers to itself
        if (curr == 1) {
            int len = freqs[i].count;
            if (len % 2 == 0) len--;
            if (len > max_len) max_len = len;
            continue;
        }
        
        int current_len = 0;
        long long temp = curr;
        
        while (1) {
            int c = get_count(freqs, unique_count, temp);
            if (c >= 2) {
                long long next_val = temp * temp;
                int c_next = get_count(freqs, unique_count, next_val);
                if (c_next >= 1) {
                    current_len += 2;
                    temp = next_val;
                } else {
                    current_len += 1;
                    break;
                }
            } else if (c == 1) {
                current_len += 1;
                break;
            } else {
                break;
            }
        }
        if (current_len > max_len) {
            max_len = current_len;
        }
    }
    
    free(freqs);
    return max_len;
}