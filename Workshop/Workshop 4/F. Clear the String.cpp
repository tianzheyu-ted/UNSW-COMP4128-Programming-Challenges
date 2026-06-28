
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    string str;
    cin >> str;

    vector<vector<int>> dp(n, vector<int>(n, 1e9));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
        for (int j = 0; j < i; j++) {
            dp[i][j] = 0;
        }
    }


    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            dp[i][i + length - 1] = 1 + dp[i + 1][i + length - 1];
            for (int j = i + 1; j < i + length; j++) {
                if (str[j] == str[i]) {
                    dp[i][i + length - 1] = min(dp[i][i + length - 1], dp[i + 1][j - 1] + dp[j][i + length - 1]);
                }
            }
        }
    }
   
    cout << dp[0][n - 1] << '\n';
}