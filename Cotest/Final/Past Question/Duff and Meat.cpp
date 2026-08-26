
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long result = 0;
    int lowest_price = 1e8;
    
    for (int i = 0; i < n; i++) {
        int a, p;
        cin >> a >> p;
        lowest_price = min(lowest_price, p);
        result += lowest_price * a;
    }

    cout << result << '\n';
}