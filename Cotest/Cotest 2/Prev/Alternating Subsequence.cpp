
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> a(n, -1);
        for (int j = 0; j < n; j++) {
            cin >> a[j];
        }

        long long sum = 0;
        int current_largest = a[0];
        bool positive_section = (a[0] > 0);
        for (int j = 1; j < n; j++) {
            if (a[j] < 0 && positive_section) {
                sum += current_largest;
                current_largest = a[j];
                positive_section = false;
            } else if (a[j] > 0 && !positive_section) {
                sum += current_largest;
                current_largest = a[j];
                positive_section = true;
            } else {
                current_largest = max(current_largest, a[j]);
            }
        }

        sum += current_largest;

        cout << sum << '\n';
    }
}