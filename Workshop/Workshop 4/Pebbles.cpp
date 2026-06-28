
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


pair<int, int> index_to_coordinate(int index, int n);
int coordinate_to_index(pair<int, int> coordinate, int n);


int main() {
    int n;
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    int max_mask_limit = 1 << (n + 1);

    vector<vector<long long>> dp(1 << (n + 2), vector<long long>(n * n + 1, -1));
    dp[0][0] = 0;

    for (int i = 0; i < n * n; i++) {
        pair<int, int> coordinate = index_to_coordinate(i, n);
        for (long long old_mask = 0; old_mask < (1 << (n + 1)); old_mask++) {
            if (dp[old_mask][i] == -1) continue;
            
            // Not Place 
            long long new_mask_0 = (old_mask << 1) & (max_mask_limit - 1);
            dp[new_mask_0][i + 1] = max(dp[new_mask_0][i + 1], dp[old_mask][i]);

            // Place
            bool can_place = true;

            if (coordinate.second > 0 && (old_mask & (1 << 0))) can_place = false;
            if (coordinate.first > 0) {
                if ((coordinate.second > 0 && old_mask & (1 << n))) {
                    can_place = false;
                }

                if ((old_mask & (1 << (n - 1)))) {
                    can_place = false;
                }

                if (coordinate.second < n - 1 && (old_mask & (1 << (n - 2)))) {
                    can_place = false;
                }
            }

            if (can_place) {
                long long new_mask_1 = ((old_mask << 1) & (max_mask_limit - 1)) + 1;
                dp[new_mask_1][i + 1] = max(dp[new_mask_1][i + 1], dp[old_mask][i] + board[coordinate.first][coordinate.second]);
            }
        }
    }

    long long result = 0;
    for (long long i = 0; i < (1 << (n + 1)); i++) {
        result = max(result, dp[i][n * n]);
    }

    cout << result << '\n';

    // vector<vector<long long>> dp(2 << (n * n), vector<long long>(n * n, -1));
    // for (int i = 0; i < n * n; i++) {
    //     dp[0][i] = 0;
    // }

    // for (int i = 0; i < n * n; i++) {
    //     for (long long mask = 1; mask < (2 << i); mask++) {
    //         pair<int, int> current = index_to_coordinate(i, n);
    //         int p1 = coordinate_to_index({current.first - 1, current.second - 1}, n);
    //         int p2 = coordinate_to_index({current.first, current.second - 1}, n);
    //         int p3 = coordinate_to_index({current.first - 1, current.second}, n);
    //         long long prev = mask | (~(1 << p1 + 1 << p2 + 1 << p3));
    //         dp[mask][i] = max(
    //             dp[mask][i - 1],
    //             dp[prev][i] + board[current.first][current.second]
    //         );
    //     }
    // }

    // vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         // cout << "i: " << i << " j: " << j << '\n';

    //         dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    //         if (i - 2 >= 0) {
    //             dp[i][j] = max(dp[i][j], dp[i - 2][j] + board[i - 1][j - 1]);
    //         }
            
    //         if (j - 2 >= 0) {
    //             dp[i][j] = max(dp[i][j], dp[i][j - 2] + board[i - 1][j - 1]);
    //         }
    //     }
    // }

    // cout << dp[n][n] << '\n';
}

pair<int, int> index_to_coordinate(int index, int n) {
    int y = index % n;
    int x = (index - y) / n;
    return {x, y};
}

int coordinate_to_index(pair<int, int> coordinate, int n) {
    return coordinate.first * n + coordinate.second;
}