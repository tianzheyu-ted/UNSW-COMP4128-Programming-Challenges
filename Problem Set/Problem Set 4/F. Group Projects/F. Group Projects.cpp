#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        vector<vector<long long>> next_dp(n + 1, vector<long long>(k + 1, 0));
        int diff = (i == 0) ? 0 : (a[i] - a[i - 1]);

        for (int q = 0; q <= i; q++) {
            for (int j = 0; j <= k; j++) {
                if (dp[q][j] == 0) continue;

                int nj = j + q * diff; 
                if (nj > k) continue;

                if (q + 1 <= n) {
                    next_dp[q + 1][nj] = (next_dp[q + 1][nj] + dp[q][j]) % MOD;
                }
                
                next_dp[q][nj] = (next_dp[q][nj] + dp[q][j] * (q + 1)) % MOD;
                
                if (q > 0) {
                    next_dp[q - 1][nj] = (next_dp[q - 1][nj] + dp[q][j] * q) % MOD;
                }
            }
        }
        dp = move(next_dp);
    }

    long long result = 0;
    for (int i = 0; i <= k; i++) {
        result = (result + dp[0][i]) % MOD;
    }

    cout << result << '\n';
    return 0;
}