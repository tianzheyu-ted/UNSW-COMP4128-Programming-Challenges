
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Smallest Prime Factor
    auto sieve_eratosthenes = [] (int max) -> vector<int> {
        vector<int> spf(max + 1, 0);
        for (int i = 1; i <= max; ++i) {
            spf[i] = i;
        }
        for (int i = 2; i * i <= max; ++i) {
            if (spf[i] == i) {
                for (int j = i * i; j <= max; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
        return spf;
    };

    vector<int> spf = sieve_eratosthenes(1e7);

    vector<int> ans_d1(n);
    vector<int> ans_d2(n);

    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        
        int p = spf[a];
        int d1 = 1;
        int temp_a = a;
        
        while (temp_a % p == 0) {
            d1 *= p;
            temp_a /= p;
        }
        
        int d2 = temp_a;
        
        if (d2 == 1) {
            ans_d1[i] = -1;
            ans_d2[i] = -1;
        } else {
            ans_d1[i] = d1;
            ans_d2[i] = d2;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans_d1[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    for (int i = 0; i < n; ++i) {
        cout << ans_d2[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}