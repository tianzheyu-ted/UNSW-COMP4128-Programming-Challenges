
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
    int m, n, k;
    cin >> n >> m >> k;

    vector<long long> satisfactions(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> satisfactions[i];
    }

    vector<vector<long long>> rules(n, vector<long long>(n, 0));
    for (int i = 0; i < k; i++) {
        int x, y;
        long long c;
        cin >> x >> y >> c;
        rules[x - 1][y - 1] = c;
    }

    vector<vector<long long>> dp((1 << n), vector<long long>(n, 0));

    for (int i = 0; i < n; i++) {
        int mask = 1 << i;
        dp[mask][i] = satisfactions[i];
    }

    for (int mask = 1; mask < (1 << (n)); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                for (int j = 0; j < n; j++) {
                    if ((mask & (1 << j)) == 0) {
                        int new_mask = mask + (1 << j);
                        dp[new_mask][j] = max(dp[new_mask][j], dp[mask][i] + satisfactions[j] + rules[i][j]);
                    }
                }
            }
        }
    }

    long long result = 0;
    for (int mask = 1; mask < (1 << (n)); mask++) { 
        if (__builtin_popcount(mask) == m) {
            for (int i = 0; i < n; i++) {
                result = max(result, dp[mask][i]);
            }
        }
            
    }

    cout << result << '\n';
}