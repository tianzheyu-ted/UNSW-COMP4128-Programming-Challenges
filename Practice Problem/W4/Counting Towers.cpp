
#include <vector>
#include <iostream>

using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    int t;
    cin >> t;

    int max_height = 0;
    vector<int> heights(t, -1);

    for (int i = 0; i < t; i++) {
        cin >> heights[i];
        max_height = max(max_height, heights[i]);
    }

    vector<vector<long long>> dp(max_height + 1, vector<long long>(2, -1));
    // 0 means seprated in level i, 1 means not seprated in level i
    dp[1][0] = 1;
    dp[1][1] = 1;

    for (int j = 2; j <= max_height; j++) {
        dp[j][0] = (4 * dp[j - 1][0] + dp[j - 1][1]) % MOD;
        dp[j][1] = (2 * dp[j - 1][1] + dp[j - 1][0]) % MOD;
    }

    for (auto height : heights) {
        cout << (dp[height][0] + dp[height][1]) % MOD << '\n';
    }
}