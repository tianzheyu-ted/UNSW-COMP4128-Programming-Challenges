
#include <iostream>

using namespace std;

bool check_k(int k, int n, string& rounds, char winner);

int main() {

    int n;
    cin >> n;

    string rounds;
    cin >> rounds;

    int a = 0;
    int b = 0;
    for (int i = 0; i < n; i++) {
        if (rounds[i] == 'A') a++;
        if (rounds[i] == 'B') b++;
    }

    char winner;
    if (a > b) winner = 'A';
    if (b > a) winner = 'B';

    int lo = 0;
    int hi = (n - 1) / 2;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (check_k(mid, n, rounds, winner)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << 2 * hi + 1 << '\n';

    string result(n, '_');
    int loser_left = hi;
    int winner_left = hi + 1;
    bool winner_block = (hi == 0);
    for (int i = 0; i < n; i++) {
        if (!winner_block) {
            if (rounds[i] != winner) {
                loser_left--;
                result[i] = rounds[i];
            }
            if (loser_left == 0) winner_block = true;
        } else {
            if (rounds[i] == winner && winner_left > 0) {
                winner_left--;
                result[i] = rounds[i];
            }
        }
    }

    cout << result << '\n';
}


bool check_k(int k, int n, string& rounds, char winner) {
    int loser_left = k;
    int winner_left = k + 1;
    bool winner_block = (k == 0);

    for (int i = 0; i < n; i++) {
        if (!winner_block) {
            if (rounds[i] != winner) loser_left--;
            if (loser_left == 0) winner_block = true;
        } else {
            if (rounds[i] == winner) winner_left--;
        }
    }

    return (loser_left <= 0) && (winner_left <= 0);
}

