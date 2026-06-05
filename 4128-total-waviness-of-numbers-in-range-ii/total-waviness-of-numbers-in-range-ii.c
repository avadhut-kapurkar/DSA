#include <stdio.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll cnt;   // number of valid numbers
    ll sum;   // total waviness
} Node;

char digits[20];
int len;

Node dp[20][2][11][11];
int vis[20][2][11][11];

Node dfs(int pos, int tight, int started, int prev1, int prev2) {
    if (pos == len) {
        Node res = {1, 0};
        return res;
    }

    if (!tight && vis[pos][started][prev1][prev2]) {
        return dp[pos][started][prev1][prev2];
    }

    int limit = tight ? (digits[pos] - '0') : 9;

    Node ans = {0, 0};

    for (int d = 0; d <= limit; d++) {
        int ntight = tight && (d == limit);

        if (!started && d == 0) {
            Node child = dfs(pos + 1, ntight, 0, 10, 10);

            ans.cnt += child.cnt;
            ans.sum += child.sum;
        } else {
            if (!started) {
                Node child = dfs(pos + 1, ntight, 1, d, 10);

                ans.cnt += child.cnt;
                ans.sum += child.sum;
            } else {
                int add = 0;

                if (prev2 != 10) {
                    if ((prev1 > prev2 && prev1 > d) ||
                        (prev1 < prev2 && prev1 < d)) {
                        add = 1;
                    }
                }

                Node child = dfs(pos + 1, ntight, 1, d, prev1);

                ans.cnt += child.cnt;
                ans.sum += child.sum + (ll)add * child.cnt;
            }
        }
    }

    if (!tight) {
        vis[pos][started][prev1][prev2] = 1;
        dp[pos][started][prev1][prev2] = ans;
    }

    return ans;
}

ll solve(ll n) {
    if (n < 0) return 0;

    sprintf(digits, "%lld", n);
    len = (int)strlen(digits);

    memset(vis, 0, sizeof(vis));

    Node res = dfs(0, 1, 0, 10, 10);
    return res.sum;
}

long long totalWaviness(long long num1, long long num2) {
    return solve(num2) - solve(num1 - 1);
}

/* Example usage
int main() {
    printf("%lld\n", totalWaviness(120, 130));   // 3
    printf("%lld\n", totalWaviness(198, 202));   // 3
    printf("%lld\n", totalWaviness(4848, 4848)); // 2
    return 0;
}
*/