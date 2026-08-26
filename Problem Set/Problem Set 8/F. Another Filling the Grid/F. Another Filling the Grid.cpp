
#include <vector>
#include <iostream>

using namespace std;

static long long MOD = 1e9 + 7;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    auto power = [&](long long base, long long exp) -> long long {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return res;
    };

    auto nCr = [&] (int n, int k) -> long long {
        static vector<long long> fact = {1};
        static vector<long long> inv = {1};
        if (n >= fact.size()) {
            int old_size = fact.size();
            int new_size = n + 1; 
            fact.resize(new_size);
            inv.resize(new_size);
            for (int i = old_size; i < new_size; ++i) {
                fact[i] = (fact[i - 1] * i) % MOD;
            }
            inv[new_size - 1] = power(fact[new_size - 1], MOD - 2);
            for (int i = new_size - 2; i >= old_size; --i) {
                inv[i] = (inv[i + 1] * (i + 1)) % MOD;
            }
        }
        if (k < 0 || k > n) return 0;
        return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
    };

    long long result = 0;
    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0) {
            result += (nCr(n, i) * power(power(k - 1, i) * power(k, n - i) - power(k - 1, n), n)) % MOD;
            result = (result + MOD) % MOD;
        } else {
            result -= (nCr(n, i) * power(power(k - 1, i) * power(k, n - i) - power(k - 1, n), n)) % MOD;
            result = (result + MOD) % MOD;
        }
    }

    cout << result << '\n';
}