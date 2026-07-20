
#include <iostream>

using namespace std;

int main() {
    long long a, b, n;
    cin >> a >> b;

    long long d;
    cin >> n >> d;

    for (int k = 0; k <= n; k++) {
        if (d == a*k - b*(n - k)) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
}

