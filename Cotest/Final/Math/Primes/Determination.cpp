
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    auto is_prime = [](long long n) -> bool {
        if (n < 2) return false;
        for (long long i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    };

    for (int i = 0; i < t; i++) {
        long long n;
        cin >> n;
        cout << is_prime(n) << '\n';
    }
}