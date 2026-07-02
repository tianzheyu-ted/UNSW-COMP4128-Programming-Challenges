
#include <set>
#include <vector>
#include <iostream>


using namespace std;


int main() {
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> books(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        cin >> books[i].first;
    }

    for (int i = 0; i < n; i++) {
        cin >> books[i].second;
    }

    vector<int> dp(x + 1, 0);
    dp[0] = 0;

    for (auto& book : books) {
        for (int i = x; i >= book.first; i--) {
            dp[i] = max(dp[i], dp[i - book.first] + book.second);
        }
    }

    cout << dp[x] << '\n';
}