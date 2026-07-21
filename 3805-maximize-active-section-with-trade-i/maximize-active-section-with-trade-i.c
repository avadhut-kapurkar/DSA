#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int maxActiveSectionsAfterTrade(char* s) {
    int n = strlen(s);
    int initial_1s = 0;
    
    // Count total initial '1's
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') initial_1s++;
    }

    // Dynamic arrays to store the lengths of 0-blocks and internal 1-blocks
    int* Z = (int*)malloc(n * sizeof(int));
    int* O = (int*)malloc(n * sizeof(int));
    int z_count = 0;
    int o_count = 0;

    int i = 0;
    // Skip any leading '1's as they are not internal
    while (i < n && s[i] == '1') {
        i++;
    }

    // Parse the string for block lengths
    while (i < n) {
        int z_len = 0;
        while (i < n && s[i] == '0') {
            z_len++;
            i++;
        }
        Z[z_count++] = z_len; // Record a 0-block

        if (i < n) {
            int o_len = 0;
            while (i < n && s[i] == '1') {
                o_len++;
                i++;
            }
            // Only record the 1-block if it is followed by a '0' (meaning it's internal)
            if (i < n) {
                O[o_count++] = o_len;
            }
        }
    }

    // If there is no internal 1-block bounded by 0s, a trade is impossible
    if (z_count < 2) {
        free(Z);
        free(O);
        return initial_1s;
    }

    // Precalculate prefix and suffix max arrays for 0-blocks to query rapidly
    int* pref = (int*)malloc(z_count * sizeof(int));
    int* suff = (int*)malloc(z_count * sizeof(int));

    pref[0] = Z[0];
    for (int j = 1; j < z_count; j++) {
        pref[j] = (Z[j] > pref[j-1]) ? Z[j] : pref[j-1];
    }

    suff[z_count-1] = Z[z_count-1];
    for (int j = z_count - 2; j >= 0; j--) {
        suff[j] = (Z[j] > suff[j+1]) ? Z[j] : suff[j+1];
    }

    int max_1s = initial_1s;

    // Simulate flipping every internal 1-block to '0'
    for (int j = 0; j < o_count; j++) {
        // Find the length of the new massive 0-block created
        int merged = Z[j] + O[j] + Z[j+1];
        
        // Find the largest 0-block available elsewhere in the string
        int left_max = (j > 0) ? pref[j-1] : 0;
        int right_max = (j + 2 < z_count) ? suff[j+2] : 0;
        int other_max = (left_max > right_max) ? left_max : right_max;

        // The best 0-block to convert to '1's
        int best_0_block = (merged > other_max) ? merged : other_max;
        
        // Calculate the simulated net active sections result
        int current_1s = initial_1s - O[j] + best_0_block;
        if (current_1s > max_1s) {
            max_1s = current_1s;
        }
    }

    // Memory cleanup
    free(Z);
    free(O);
    free(pref);
    free(suff);

    return max_1s;
}