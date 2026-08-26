
#include <vector>
#include <iostream>

using namespace std;


int main() {
    int n, k;
    cin >> n >> k;

    string spots;
    cin >> spots;

    int current = 1;
    vector<int> left_most_routes(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (current > n) break;
        if (spots[i - 1] == '1') {
            for (int j = current; j <= min(i + k, n); j++) {
                left_most_routes[j] = i;
                current++;
            }
        }
    }

    vector<long long> dp(n + 1, 1e18);
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        
        // int start = max(1, i - k);
        // int end = min(n, i + k);
        // long long cost_use_route = 1e18;

        // for (int j = start; j <= end; j++) {
        //     if (spots[j - 1] == '1') {
        //         int prev_uncover = j - k - 1;
        //         if (prev_uncover  > 0) {
        //             cost_use_route = min(dp[prev_uncover] + j, cost_use_route);
        //         } else {
        //             cost_use_route = min((long long)j, cost_use_route);
        //         }
        //     }
        // }

        long long cost_use_route = 1e18;
        if (left_most_routes[i] != -1) {
            int prev_uncover = left_most_routes[i] - k - 1;
            if (prev_uncover  > 0) {
                cost_use_route = min(dp[prev_uncover] + left_most_routes[i], cost_use_route);
            } else {
                cost_use_route = min((long long)left_most_routes[i], cost_use_route);
            }
        }

        dp[i] = min(dp[i - 1] + i, cost_use_route);
    }

    cout << dp[n] << '\n';
}