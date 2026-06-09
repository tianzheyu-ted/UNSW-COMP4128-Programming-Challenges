
#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int test_cases_num;
    cin >> test_cases_num;

    for (int i = 0; i < test_cases_num; i++) {
        int n;
        cin >> n;

        char c;
        cin >> c;

        string s;
        cin >> s;

        if (c == 'g') {
            cout << 0 << '\n';
            continue;
        }

        int prev = -1;
        int max_gap = 0;
        for (int j = 0; j < n * 2; j++) {
            if (s[j % n] == c && j < n) {
                if (prev == -1) {
                    prev = j;
                }
            } else if (s[j % n] == 'g' && prev != -1) {
                max_gap = max(max_gap, j - prev);
                prev = -1;
            }
        }

        cout << max_gap << '\n';
    }
}