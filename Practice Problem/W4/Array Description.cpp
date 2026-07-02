
#include <vector>
#include <iostream>

using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> array(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

    if (array[0] != 0) {
        dp[1][array[0]] = 1;
    } else {
        for (int i = 1; i <= m; i++) {
            dp[1][i] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (array[i - 1] != 0) {
            int left, right;
            if (array[i - 1] == 1) {
                left = array[i - 1];
                right = array[i - 1] + 1;
            } else if (array[i - 1] == m) {
                right = array[i - 1];
                left = array[i - 1] - 1;
            } else {
                right = array[i - 1] + 1;
                left = array[i - 1] - 1;
            }

            for (int prev = left; prev <= right; prev++) {
                dp[i][array[i - 1]] = (dp[i][array[i - 1]] + dp[i - 1][prev]) % MOD;
            }

        } else {
            for (int curr = 1; curr <= m; curr++) {
                int left, right;
                if (curr == 1) {
                    left = curr;
                    right = curr + 1;
                } else if (curr == m) {
                    right = curr;
                    left = curr - 1;
                } else {
                    right = curr + 1;
                    left = curr - 1;
                }

                for (int prev = left; prev <= right; prev++) {
                    dp[i][curr] = (dp[i][curr] + dp[i - 1][prev]) % MOD;
                }
            }
        }
    }

    if (array[n - 1] != 0) {
        cout << dp[n][array[n - 1]] << '\n';
        return 0;
    }


    long long result = 0;
    for (int i = 1; i <= m; i++) {
        result = (result + dp[n][i]) % MOD;
    }

    cout << result << '\n';
}