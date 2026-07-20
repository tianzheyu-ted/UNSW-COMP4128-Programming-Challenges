
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            result += abs(a[i] - a[j]);
        }
    }

    cout << result << '\n';
}