
#include <vector>
#include <iostream>


using namespace std;

struct Tree {
    int color;
    vector<long long> paints;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<Tree> trees(n + 1, {-1, vector<long long>(m + 1)});
    for (int i = 1; i <= n; i++) {
        cin >> trees[i].color;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> trees[i].paints[j];
        }
    }

    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(k + 1, vector<long long>(m + 1, 1e18)));

    for (int i = 1; i <= m; i++) {
        if (trees[1].color != 0) {
            if (trees[1].color == i) {
                dp[1][1][i] = 0;
            }
        } else {
            dp[1][1][i] = trees[1].paints[i];
        }
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int q = 1; q <= m; q++) {
                if (trees[i].color != 0) {
                    if (q == trees[i].color) {
                        for (int p = 1; p <= m; p++) {
                            if (p == q) {
                                dp[i][j][q] = min(dp[i - 1][j][p], dp[i][j][q]);
                            } else {
                                dp[i][j][q] = min(dp[i - 1][j - 1][p], dp[i][j][q]);
                            }
                        }
                    }
                } else {
                    for (int p = 1; p <= m; p++) {
                        if (p == q) {
                            dp[i][j][q] = min(dp[i - 1][j][p] + trees[i].paints[q], dp[i][j][q]);
                        } else {
                            dp[i][j][q] = min(dp[i - 1][j - 1][p] + trees[i].paints[q], dp[i][j][q]);
                        }
                    }
                }
            }
        }
    }

    long long result = 1e18;
    for (int i = 1; i <= m; i++) {
        result = min(result, dp[n][k][i]);
    } 

    if (result == 1e18) {
        result = -1;
    }

    cout << result << '\n';
}