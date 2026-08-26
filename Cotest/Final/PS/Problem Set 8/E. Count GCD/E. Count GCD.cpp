
#include <vector>
#include <iostream>

using namespace std;

static int MOD = 998244353;

int main() {
    int t;
    cin >> t;

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

    for (int i = 0; i < t; i++) {
        int n;
        long long m;
        cin >> n >> m;

        vector<long long> a(n, -1);
        for (int j = 0; j < n; j++) {
            cin >> a[j];
        }

        long long result = 1;

        for (int j = 1; j < n; j++) {
            long long curr = a[j];
            long long prev = a[j - 1];

            if (prev % curr != 0) {
                result = 0;
                break;
            }

            long long X = prev / curr;
            long long K = m / curr;

            auto factors = prime_factorization(X);

            vector<int> primes;
            for (auto f : factors) {
                primes.push_back(f.first);
            }

            int k = primes.size();
            long long current_ways = 0;

            for (int mask = 0; mask < (1 << k); mask++) {
                int bits = 0;
                long long prod = 1;
                
                for (int bit = 0; bit < k; bit++) {
                    if ((mask >> bit) & 1) {
                        bits++;
                        prod *= primes[bit];
                    }
                }

                if (bits % 2 == 1) {
                    current_ways -= K / prod;
                } else {
                    current_ways += K / prod;
                }
            }

            result = (result * (current_ways % MOD)) % MOD;
        }

        cout << result << '\n';
    }
}