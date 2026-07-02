
#include <set>
#include <cmath>
#include <vector>
#include <iostream>


using namespace std;

const long long MOD = round(pow(10, 9)) + 7;

int main() {
    int n;
    cin >> n;

    set<pair<int, int>> grid;

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            if (row[j] == '*') {
                grid.insert({i, j});
            }
        }
    }

    if (grid.count({0, 0})) {
        cout << 0 << '\n';
        return 0;
    }

    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    dp[0][0] = 1;

    bool down_block = false;
    bool right_block = false;

    for (int i = 1; i < n; i++) {
        if (grid.count({i, 0}) || down_block) {
            down_block = true;
            dp[i][0] = -1;
        } else {
            dp[i][0] = 1;
        }

        if (grid.count({0, i}) || right_block) {
            right_block = true;
            dp[0][i] = -1;
        } else {
            dp[0][i] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (grid.count({i, j})) {
                dp[i][j] = -1;
            } else {
                int left = 0;
                if (dp[i - 1][j] != -1) left = dp[i - 1][j];

                int up = 0;
                if (dp[i][j - 1] != -1) up = dp[i][j - 1];

                dp[i][j] = (left + up) % MOD;
            }
        }
    }

    if (dp[n - 1][n - 1] == -1) {
        cout << 0 << '\n';
    } else {
        cout << dp[n - 1][n - 1] << '\n';
    }
}