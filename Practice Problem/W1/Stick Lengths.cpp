
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long sum = 0;
    vector<long long> p(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        // sum += p[i];
    }

    sort(p.begin(), p.end());

    long long target = p[n / 2];

    // long long avg = sum / n;

    long long cost = 0;
    for (int i = 0; i < n; i++) {
        cost += abs(p[i] - target);
    }

    // cout << sum << '\n' << avg << '\n';

    cout << cost << '\n';
}