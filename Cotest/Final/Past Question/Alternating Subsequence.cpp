
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        bool sign;
        long long sum = 0;
        long long subsequence_max;

        for (int j = 0; j < n; j++) {
            long long a;
            cin >> a;

            if (j == 0) {
                sign = (a > 0);
                subsequence_max = a;
            } else {
                if (sign != (a > 0)) {
                    sum += subsequence_max;
                    subsequence_max = a;
                    sign = (a > 0);
                } else {
                    subsequence_max = max(subsequence_max, a);
                }
            }
        }

        sum += subsequence_max;

        cout << sum << '\n';
    }
}