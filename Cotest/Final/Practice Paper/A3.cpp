
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long n, k, x, y;

    cin >> n >> k;

    auto exgcd = [](auto& self, long long a, long long b, long long& x, long long& y) -> long long {
        if (b == 0) {
            x = 1; 
            y = 0;
            return a;
        }
        long long x1, y1;
        long long d = self(self, b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
        return d;
    };

    if (exgcd(exgcd, n, k, x, y) == 1) {
        cout << "VALID\n";
        return 0;
    }
    
    cout << "INVALID\n";
}