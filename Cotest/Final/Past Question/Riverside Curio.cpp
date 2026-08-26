
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> m(n, -1);
    vector<int> T(n, -1);

    // T[i] = m[i] + d[i] + 1;
    // T[i] >= m[i] + 1
    // T[i - 1] <= T[i] <= T[i - 1] + 1

    // T[i] >= m[i] + 1
    for (int i = 0; i < n; i++) {
        cin >> m[i];
        T[i] = m[i] + 1;
    }

    //      T[i] <= T[i - 1] + 1
    // ->   T[i - 1] >= T[i] - 1
    for (int i = n - 1; i > 0; i--) {
        if (T[i - 1] < T[i] - 1) {
            T[i - 1] = T[i] - 1;
        }
    }

    // T[i - 1] <= T[i]
    for (int i = 1; i < n; i++) {
        if (T[i] < T[i - 1]) {
            T[i] = T[i - 1];
        }
    }

    long long result = 0;
    for (int i = 0; i < n; i++) {
        result += T[i] - m[i] - 1;
    }

    cout << result << '\n';
}