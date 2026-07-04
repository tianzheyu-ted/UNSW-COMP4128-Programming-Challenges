
#include <set>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long sum = 0;
    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    if (sum % 2) {
        cout << "NO\n";
        return 0;
    }

    set<long long> s1;
    long long curr_sum = 0;
    long long half = sum / 2;
    for (int i = 0; i < n; i++) {
        s1.insert(a[i]);
        curr_sum += a[i];
        if (s1.count(curr_sum - half)) {
            cout << "YES\n";
            return 0;
        }
    }

    set<long long> s;
    curr_sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        s.insert(a[i]);
        curr_sum += a[i];
        if (s.count(curr_sum - half)) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
}