
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    auto prime_factorization = [] (int n) -> vector<pair<int, int>> {
        vector<pair<int, int>> factors;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                int counter = 0;
                while (n % i == 0) {
                    counter++;
                    n = (int) n / i;
                }
                factors.push_back({i, counter});
            }
        }
        if (n > 1) {
            factors.push_back({n, 1});
        }
        return factors;
    };

    auto factors = prime_factorization(n);

    int minimum = 1;
    int maximum_power = 0;
    for (auto factor : factors) {
        minimum *= factor.first;
        maximum_power = max(factor.second, maximum_power);
    }

    cout << minimum << ' ';

    int second_power = 0;
    while (maximum_power > (1 << second_power)) {
        second_power++;
    }

    for (auto factor : factors) {
        if (factor.second != (1 << second_power)) {
            cout << second_power + 1 << '\n';
            return 0;
        }
    }

    cout << second_power << '\n';
}