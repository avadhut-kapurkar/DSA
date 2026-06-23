class Solution:
    def zigZagArrays(self, n: int, l: int, r: int) -> int:
        MOD = 10**9 + 7
        k = r - l + 1
        
        # Base case: Arrays of length 2
        dp_up = [0] * (k + 1)
        dp_down = [0] * (k + 1)
        
        for j in range(1, k + 1):
            dp_up[j] = j - 1
            dp_down[j] = k - j
            
        # Build sequences from length 3 up to n
        for _ in range(3, n + 1):
            next_up = [0] * (k + 1)
            next_down = [0] * (k + 1)
            
            # Compute next_up using prefix sums
            running_sum_down = 0
            for j in range(1, k + 1):
                next_up[j] = running_sum_down
                running_sum_down = (running_sum_down + dp_down[j]) % MOD
                
            # Compute next_down using suffix sums
            running_sum_up = 0
            for j in range(k, 0, -1):
                next_down[j] = running_sum_up
                running_sum_up = (running_sum_up + dp_up[j]) % MOD
                
            dp_up = next_up
            dp_down = next_down
            
        # The answer is the sum of all valid sequences of length n
        total_valid_arrays = (sum(dp_up) + sum(dp_down)) % MOD
        
        return total_valid_arrays