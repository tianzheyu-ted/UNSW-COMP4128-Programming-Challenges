
#include <map>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int max_val = 0;
    vector<int> freq(100000,0);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
        max_val = max(max_val, a);
    }

    vector<long long> dp(max_val + 1, -1);

    dp[0] = 0;

    if (max_val >= 1) {
        dp[1] = freq[1];
    }
    

    for (int i = 2; i <= max_val; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + (long long)freq[i] * i);
    }

    cout << dp[max_val] << '\n';
}