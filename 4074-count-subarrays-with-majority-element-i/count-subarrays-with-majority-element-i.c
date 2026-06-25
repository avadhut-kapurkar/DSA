long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    long long ans = 0;

    for (int i = 0; i < numsSize; i++) {
        int countTarget = 0;

        for (int j = i; j < numsSize; j++) {
            if (nums[j] == target)
                countTarget++;

            int len = j - i + 1;

            if (countTarget > len / 2)
                ans++;
        }
    }

    return ans;
}