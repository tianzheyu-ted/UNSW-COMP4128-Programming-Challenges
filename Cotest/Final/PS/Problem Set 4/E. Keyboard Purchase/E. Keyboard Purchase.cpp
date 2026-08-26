
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    vector<vector<int>> counter(m, vector<int>(m, 0));
    for (int i = 0; i < n - 1; i++) {
        int u = s[i] - 'a';
        int v = s[i + 1] - 'a';
        if (u != v) {
            counter[u][v]++;
            counter[v][u]++;
        }
    }

    vector<int> cost(1 << m, 0);
    for (int mask = 1; mask < (1 << m); mask++) {
        int i = __builtin_ctz(mask); 
        int prev_mask = mask - (1 << i);
        
        cost[mask] = cost[prev_mask];
        
        for (int j = 0; j < m; j++) {
            if (i == j) continue;
            
            if (prev_mask & (1 << j)) {
                cost[mask] -= counter[i][j];
            } else {
                cost[mask] += counter[i][j];
            }
        }
    }

    vector<long long> dp(1 << m, 1e18);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << m); mask++) {
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) continue;
            int next = mask + (1 << i);
            dp[next] = min(dp[next], dp[mask] + cost[next]);
        }   
    }
    
    cout << dp[(1 << m) - 1] << '\n';
}