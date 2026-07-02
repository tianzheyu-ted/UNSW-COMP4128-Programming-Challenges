
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;

    map<long long, int> s;
    vector<long long> a(n, -1);
    vector<long long> diff(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        diff[i] = x - a[i];
        s[a[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        if (s.count(diff[i]) && i != s[diff[i]]) {
            cout << i + 1 << ' ' << s[diff[i]] + 1 << '\n';
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
}
