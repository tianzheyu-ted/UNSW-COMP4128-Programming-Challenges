
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<long long>> heights(2, vector<long long>(n, -1));
    for (int i = 0; i < n; i++) {
        cin >> heights[0][i];
    }
    for (int i = 0; i < n; i++) {
        cin >> heights[1][i];
    }

    vector<vector<long long>> dp(2, vector<long long>(n, -1));

    dp[0][n - 1] = heights[0][n - 1];
    dp[1][n - 1] = heights[1][n - 1];
    
    if (n - 2 >= 0) {
        dp[0][n - 2] = heights[0][n - 2] + dp[1][n - 1];
        dp[1][n - 2] = heights[1][n - 2] + dp[0][n - 1];
    }
    
    for (int i = n - 3; i >= 0; i--) {
        dp[0][i] = heights[0][i] + max({dp[1][i + 1], dp[0][i + 2], dp[1][i + 2]});
        dp[1][i] = heights[1][i] + max({dp[0][i + 1], dp[0][i + 2], dp[1][i + 2]});
    }

    cout << max(dp[0][0], dp[1][0]) << '\n';
}