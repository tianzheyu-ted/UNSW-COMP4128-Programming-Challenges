
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;

    auto check = [] (int k, int d, long long c, vector<long long>& rewards) -> bool {
        long long max_rewards_sum = 0;
        for (int i = 0; i < d; i++) {
            int current_day_in_cycle = i % (k + 1);
            if (current_day_in_cycle < rewards.size()) {
                max_rewards_sum += rewards[current_day_in_cycle];
            }
        }
        return max_rewards_sum >= c;
    };

    for (int i = 0; i < t; i++) {
        int n, d;
        long long c;
        cin >> n >> c >> d;

        vector<long long> rewards(n, 0);
        for (int j = 0; j < n; j++) {
            cin >> rewards[j];
        }

        sort(rewards.begin(), rewards.end(), [] (auto a, auto b) {
            return a > b;
        });

        int lo = 0;
        int hi = d - 1;

        if (!check(lo, d, c, rewards)) {
            cout << "Impossible\n";
            continue;
        }

        if (check(hi, d, c, rewards)) {
            cout << "Infinity\n";
            continue;
        }

        while (lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;
            if (check(mid, d, c, rewards)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        cout << lo << '\n';
    }
}