
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> temp(n + 1, 0);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        temp[l - 1] += 1;
        temp[r] -= 1;
    }

    int curr = 0;
    vector<int> freq(n, 0);

    for (int i = 0; i < n; i++) {
        curr += temp[i];
        freq[i] = curr;
    }

    sort(freq.begin(), freq.end(), [] (auto& a, auto& b) {
        return a > b;
    });

    sort(a.begin(), a.end(), [] (auto& x, auto& y) {
        return x > y;
    });

    long long result = 0;
    for (int i = 0; i < n; i++) {
        result += ((long long) freq[i]) * ((long long) a[i]);
    }

    cout << result << '\n';
}