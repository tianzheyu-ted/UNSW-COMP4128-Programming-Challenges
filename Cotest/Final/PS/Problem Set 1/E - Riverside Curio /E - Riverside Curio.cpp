
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> m(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> m[i];
    }

    vector<int> total(n, 1);
    for (int i = 1; i < n; i++) {
        int prev = total[i - 1];
        int curr_and_above = m[i] + 1;
        total[i] = max(prev, curr_and_above);
    }

    for (int i = n - 2; i >= 0; i--) {
        total[i] = max(total[i + 1] - 1, total[i]);
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += total[i] - m[i] - 1;
    }

    cout << sum << '\n';
}