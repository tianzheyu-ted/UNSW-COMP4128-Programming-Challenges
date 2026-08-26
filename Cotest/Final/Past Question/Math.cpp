
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

auto build_lpf = [](int N) {
    vector<int> lpf(N + 1);
    for (int i = 2; i <= N; i++) {
        lpf[i] = i; 
    }
    for (int i = 2; i * i <= N; i++) {
        if (lpf[i] == i) {
            for (int j = i * i; j <= N; j += i) {
                if (lpf[j] == j) {
                    lpf[j] = i; 
                }
            }
        }
    }
    return lpf;
};

auto factorize_fast = [](int x, const vector<int>& lpf) -> vector<pair<int, int>> {
    vector<pair<int, int>> factors;
    while (x > 1) {
        int p = lpf[x];
        int counter = 0;
        while (x % p == 0) {
            counter++;
            x /= p;
        }
        factors.push_back({p, counter});
    }
    return factors;
};

int main() {
    int n;
    cin >> n;

    auto lpf = build_lpf(1e6);
    auto factors = factorize_fast(n, lpf);

    
    int max_e = 0;
    long long min_n = 1;
    long long result = 1;
    for (auto factor : factors) {
        result *= factor.first;
        max_e = max(max_e, factor.second);
        min_n *= (long long) factor.first;
    }

    cout << result << ' ';

    int p = 0;
    int target_power = 1;
    while (target_power < max_e) {
        target_power *= 2;
        p++;
    }

    bool need_mul = false;
    for (auto f : factors) {
        if (f.second != target_power) {
            need_mul = true;
            break;
        }
    }

    int action = p + (need_mul ? 1 : 0);

    cout << action << '\n';
}