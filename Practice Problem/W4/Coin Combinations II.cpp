
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

const long long MOD = round(pow(10, 9)) + 7;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> coins(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    vector<long long> dp(x + 1, 0);
    dp[0] = 1;

    for (auto coin : coins) {
        for (int i = 1; i <= x; i++) {
            if (i - coin < 0) continue;
            dp[i] = (dp[i] + dp[i - coin]) % MOD; 
        }
    }

    cout << dp[x] << '\n';
}
