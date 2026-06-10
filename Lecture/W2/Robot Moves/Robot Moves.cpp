
#include <vector>
#include <iostream>

using namespace std;

bool check_m(int m, string& move_sequence, int n, int x);

int main() {
    int n, x;
    cin >> n;
    cin >> x;

    string move_sequence;
    cin >> move_sequence;

    int lo = 0;
    int hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check_m(mid, move_sequence, n, x)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << '\n';
}


bool check_m(int m, string& move_sequence, int n, int x) {
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
        int curr_step = 0;
        if (move_sequence[i - 1] == 'L') curr_step = -1;
        if (move_sequence[i - 1] == 'R') curr_step = 1;
        prefix[i] = prefix[i - 1] +  curr_step;
    }

    int final_pos = prefix[n];

    for (int i = 0; i <= n - m; i++) {
        int window_move = prefix[i + 1 + m] - prefix[i + 1];
        int remaining_step = final_pos - window_move;
        if (abs(remaining_step - x) <= m) return true;
    }

    return false;
}