
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long sum = 0;
    vector<long long> a(n, -1);
    vector<long long> prefix(n, -1);
    multiset<long long> suffix_appeared;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        suffix_appeared.insert(a[i]);
        prefix[i] = sum;
    }

    if (sum % 2) {
        cout << "NO\n";
        return 0;
    }

    long long half = sum / 2;

    multiset<long long> prefix_appeared;

    for (int i = 0; i < n; i++) {
        prefix_appeared.insert(a[i]);
        suffix_appeared.erase(suffix_appeared.find(a[i]));
        long long prefix_sum = prefix[i];
        long long suffix_sum = sum - prefix[i];

        if (prefix_sum > suffix_sum) {
            long long target = prefix_sum - half;
            if (prefix_appeared.find(target) != prefix_appeared.end()) {
                cout << "YES\n";
                return 0;
            }
        } else if (prefix_sum < suffix_sum) {
            long long target = suffix_sum - half;
            if (suffix_appeared.find(target) != suffix_appeared.end()) {
                cout << "YES\n";
                return 0;
            }
        } else {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
    return 0;
}