#include <stdio.h>
#include <stdlib.h>

// Helper function to compare integers for qsort
int cmp(const void *a, const void *b) {
    if (*(int*)a < *(int*)b) return -1;
    if (*(int*)a > *(int*)b) return 1;
    return 0;
}

// Binary search to find the index of a value in the unique sorted array
int getIndex(int *V, int K, int val) {
    int l = 0, r = K - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (V[mid] == val) return mid;
        if (V[mid] < val) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

// Renamed to match the expected auto-grader signature
int* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Step 1: Extract and sort unique values
    int* V = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        V[i] = nums[i];
    }
    qsort(V, n, sizeof(int), cmp);
    
    int K = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || V[i] != V[i - 1]) {
            V[K++] = V[i];
        }
    }
    
    // Step 2: Build the binary lifting table
    int LOG = 18; // 2^17 = 131072, enough for N <= 100,000
    int** up = (int**)malloc(K * sizeof(int*));
    for (int i = 0; i < K; i++) {
        up[i] = (int*)malloc(LOG * sizeof(int));
    }
    
    // Base case: furthest index reachable in 1 step (2^0)
    int right = 0;
    for (int i = 0; i < K; i++) {
        if (right < i) right = i;
        while (right + 1 < K && V[right + 1] <= V[i] + maxDiff) {
            right++;
        }
        up[i][0] = right;
    }
    
    // Populate the rest of the binary lifting table
    for (int step = 1; step < LOG; step++) {
        for (int i = 0; i < K; i++) {
            up[i][step] = up[ up[i][step - 1] ][step - 1];
        }
    }
    
    // Step 3: Answer queries
    int* ans = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    for (int q = 0; q < queriesSize; q++) {
        int u = queries[q][0];
        int v = queries[q][1];
        
        // Edge cases for identical node indices or equal values
        if (u == v) {
            ans[q] = 0;
            continue;
        }
        if (nums[u] == nums[v]) {
            ans[q] = 1; 
            continue;
        }
        
        int idxU = getIndex(V, K, nums[u]);
        int idxV = getIndex(V, K, nums[v]);
        
        // The graph is undirected, so direction doesn't matter (always go left to right)
        if (idxU > idxV) {
            int temp = idxU;
            idxU = idxV;
            idxV = temp;
        }
        
        int curr = idxU;
        int steps = 0;
        
        // Binary lift to find max steps while staying strictly before idxV
        for (int step = LOG - 1; step >= 0; step--) {
            if (up[curr][step] < idxV) {
                curr = up[curr][step];
                steps += (1 << step);
            }
        }
        
        // Check if one more step can reach or exceed idxV
        if (up[curr][0] < idxV) {
            ans[q] = -1; // Path doesn't exist
        } else {
            ans[q] = steps + 1;
        }
    }
    
    // Free allocated structures 
    free(V);
    for (int i = 0; i < K; i++) {
        free(up[i]);
    }
    free(up);
    
    return ans;
}