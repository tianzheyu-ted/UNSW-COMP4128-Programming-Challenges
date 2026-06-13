

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool check_k(int k, int d, long long c, vector<long long>& rewards);

int main() {
    int num_test_cases;
    cin >> num_test_cases;

    for (int i = 0; i < num_test_cases; i++) {
        int n, d;
        long long c;
        cin >> n;
        cin >> c;
        cin >> d;

        vector<long long> rewards;
        for (int j = 0; j < n; j++) {
            long long reward;
            cin >> reward;
            rewards.push_back(reward);
        }

        sort(rewards.begin(), rewards.end(), greater<int>());

        long long sum = 0;
        for (int j = 0; j < min<int>(d, n); j++) {
            sum += rewards[j];
        }

        if (sum >= c) {
            cout << "Infinity\n";
            continue;
        }

        int lo = 0;
        int hi = d - 1;

        if (!check_k(lo, d, c, rewards) && !check_k(hi, d, c, rewards)) {
            cout << "Impossible\n";
            continue;
        }

        while (lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;
            if (check_k(mid, d, c, rewards)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        cout << lo << '\n';
    }
}

bool check_k(int k, int d, long long c, vector<long long>& rewards) {
    long long coins = 0;
    for (int i = 0; i < d; i++) {
        int current_day_in_cycle = i % (k + 1);
        if (current_day_in_cycle < rewards.size()) {
            coins += rewards[current_day_in_cycle];
        }
        if (coins >= c) return true;
    }
    return coins >= c;
}