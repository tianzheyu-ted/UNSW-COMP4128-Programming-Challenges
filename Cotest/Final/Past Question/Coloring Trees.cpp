
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> colors(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        cin >> colors[i];
    }

    vector<vector<long long>> p(n + 1, vector<long long>(m + 1, -1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> p[i][j];
        }
    }

    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(k + 1, vector<long long>(m + 1, 1e18)));

    if (colors[1] == 0) {
        for (int i = 1; i <= m; i++) {
            dp[1][1][i] = p[1][i];
        }
    } else {
        dp[1][1][colors[1]] = 0;
    }

    for (int i = 1; i < n; i++) {
        for (int curr_beauty = 1; curr_beauty <= k; curr_beauty++) {
            for (int curr_color = 1; curr_color <= m; curr_color++) {
                if (colors[i + 1] == 0) {
                    for (int next_color = 1; next_color <= m; next_color++) {
                        if (next_color == curr_color) {
                            dp[i + 1][curr_beauty][next_color] = min(
                                dp[i + 1][curr_beauty][next_color],
                                dp[i][curr_beauty][curr_color] + p[i + 1][next_color]
                            );
                        } else {
                            if (curr_beauty + 1 <= k) {
                                dp[i + 1][curr_beauty + 1][next_color] = min(
                                    dp[i + 1][curr_beauty + 1][next_color],
                                    dp[i][curr_beauty][curr_color] + p[i + 1][next_color]
                                ); 
                            }
                        }
                    }
                } else {
                    int next_color = colors[i + 1];
                    if (next_color == curr_color) {
                        dp[i + 1][curr_beauty][next_color] = min(
                            dp[i + 1][curr_beauty][next_color],
                            dp[i][curr_beauty][curr_color]
                        );
                    } else {
                        if (curr_beauty + 1 <= k) {
                            dp[i + 1][curr_beauty + 1][next_color] = min(
                                dp[i + 1][curr_beauty + 1][next_color],
                                dp[i][curr_beauty][curr_color]
                            );
                        }
                    }
                }
            }
        }
    }

    long long result = 1e18;
    for (int color = 1; color <= m; color++) {
        result = min(result, dp[n][k][color]);
    }

    if (result >= 1e18) {
        cout << -1 << '\n';
    } else {
        cout << result << '\n';
    }
}