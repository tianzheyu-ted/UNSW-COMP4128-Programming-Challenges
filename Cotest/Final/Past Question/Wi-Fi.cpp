
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    
    string s;
    cin >> s;

    vector<long long> dp(n + 1, 1e18);

    dp[0] = 0;

    multiset<long long> window;
    for (int j = 1; j <= min(n, k); j++) {
        if (s[j - 1] == '1') {
            window.insert(j);
        }
    }

    for (int i = 1; i <= n; i++) {
        int old_j = i - k - 1;
        if (old_j >= 1 && s[old_j - 1] == '1') {
            long long old_cost = dp[max(0, old_j - k - 1)] + old_j;
            window.erase(window.find(old_cost));
        }

        int new_j = i + k;
        if (new_j <= n && s[new_j - 1] == '1') {
            long long new_cost = dp[i - 1] + new_j;
            window.insert(new_cost);
        }

        dp[i] = dp[i - 1] + i;
        if (!window.empty()) {
            dp[i] = min(dp[i], *window.begin());
        }
    }

    // for (int i = 1; i <= n; i++) {
    //     dp[i] = min(dp[i], dp[i - 1] + i);
    //     if (s[i - 1] == '1') {
    //         int left_uncovered = max(0, i - k - 1);
    //         long long cost_if_router = dp[left_uncovered] + i;

    //         dp[i] = min(dp[i], cost_if_router);

    //         for (int j = max(1, i - k); j <= min(n, i + k); j++) {
    //             dp[j] = min(dp[j], cost_if_router);
    //         }
    //     }
    // }

    cout << dp[n] << '\n';
}