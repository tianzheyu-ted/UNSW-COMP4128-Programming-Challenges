
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> grid(n, "");
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<string>> dp(n, vector<string>(n, ""));
    dp[0][0] = grid[0][0];

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
        dp[0][i] = dp[0][i - 1] + grid[0][i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    cout << dp[n - 1][n - 1] << '\n';
}