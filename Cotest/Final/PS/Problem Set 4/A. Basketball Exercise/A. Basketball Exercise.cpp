
#include <vector>
#include <iostream>

using namespace std;

struct Student {
    int index;
    long long height;
};

int main() {
    int n;
    cin >> n;

    vector<Student> row1(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        row1[i].index = i;
        cin >> row1[i].height;
    }

    vector<Student> row2(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        row2[i].index = i;
        cin >> row2[i].height;
    }

    if (n == 1) {
        cout << max(row1[0].height, row2[0].height) << '\n';
        return 0;
    }
    
    vector<vector<long long>> dp(2, vector<long long>(n + 1));

    dp[0][n] = row1[n - 1].height;
    dp[1][n] = row2[n - 1].height;
    dp[0][n - 1] = row1[n - 2].height + row2[n - 1].height;
    dp[1][n - 1] = row2[n - 2].height + row1[n - 1].height;

    for (int i = n - 2; i > 0; i--) {
        dp[0][i] = max(dp[1][i + 1], dp[1][i + 2]) + row1[i - 1].height;
        dp[1][i] = max(dp[0][i + 1], dp[0][i + 2]) + row2[i - 1].height;
    }

    cout << max(dp[0][1], dp[1][1]) << '\n';
}