
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> row1(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> row1[i];
    }

    vector<long long> row2(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> row2[i];
    }

    vector<vector<long long>> dp(2, vector<long long>(n, 0));
    dp[0][n - 1] = row1[n - 1];
    dp[1][n - 1] = row2[n - 1];

    if (n - 2 >= 0) {
        dp[0][n - 2] = dp[1][n - 1] + row1[n - 2];
        dp[1][n - 2] = dp[0][n - 1] + row2[n - 2];
    }

    for (int i = n - 3; i >= 0; i--) {
        dp[0][i] = max(dp[1][i + 1] + row1[i], dp[1][i + 2] + row1[i]);
        dp[1][i] = max(dp[0][i + 1] + row2[i], dp[0][i + 2] + row2[i]);
    }

    cout << max(dp[0][0], dp[1][0]) << '\n';
}