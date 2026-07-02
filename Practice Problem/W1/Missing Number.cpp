
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> array(n - 1, -1);
    for (int i = 0; i < n - 1; i++) {
        cin >> array[i];
    }

    sort(array.begin(), array.end());

    if (array[0] != 1) {
        cout << 1 << '\n';
        return 0;
    }

    if (array[n - 2] != n) {
        cout << n << '\n';
        return 0;
    }

    int prev = array[0];
    for (int i = 1; i < n - 1; i++) {
        if (array[i] != prev + 1) {
            cout << prev + 1 << '\n';
            return 0;
        }
        prev = array[i];
    }
}