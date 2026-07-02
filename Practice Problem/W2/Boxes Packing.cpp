
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
    int n;
    cin >> n;

    vector<long long> a(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    // for (auto i : a) {
    //     cout << i << ' ';
    // }
    // cout << '\n';

    int left = 0;
    int counter = n;
    for (int i = 1; i < n; i++) {
        if (a[left] < a[i]) {
            counter--;
            left++;
        }
    }

    cout << counter << '\n';
}