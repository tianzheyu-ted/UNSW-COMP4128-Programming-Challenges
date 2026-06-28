
#include <bit> 
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> satisfactions(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> satisfactions[i];
    }

    vector<vector<long long>> rules(n, vector<long long>(n, 0));
    for (int i = 0; i < k; i++) {
        int x, y;
        long long z;
        cin >> x >> y >> z;
        rules[x - 1][y - 1] = z;
    }

    vector<vector<long long>> dp(1 << n, vector<long long>(n, -1));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = satisfactions[i];
    }

    for (long long i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((1 << j) & i) {
                long long prev = i ^ (1 << j);

                if (prev == 0) continue;

                for (int q = 0; q < n; q++) {
                    if ((prev & (1 << q)) && dp[prev][q] != -1) {
                        dp[i][j] = max(
                            dp[i][j],
                            dp[prev][q] + satisfactions[j] + rules[q][j]
                        );
                    }
                    
                }
            }
        }
    }

    long long result = 0;
    for (int i = 0; i < (1 << n); i++) {
        if (__builtin_popcount(i) == m) {
            for (int j = 0; j < n; j++) {
                result = max(result, dp[i][j]);
            }
        }
    }

    cout << result << '\n';
}