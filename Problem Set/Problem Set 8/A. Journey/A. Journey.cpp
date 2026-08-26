
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<double> dp(n + 1, 0.0);
    for (int i = n - 1; i > 0; i--) {
        double i_d = (double)i;
        double n_d = (double)n;
        dp[i] = (1.0 / (1.0 - (i_d / n_d)) * ((n_d - i_d) / n_d * (dp[i + 1] + 1.0) + i_d / n_d));
    }

    cout << fixed << setprecision(10) << dp[1] << '\n';
}