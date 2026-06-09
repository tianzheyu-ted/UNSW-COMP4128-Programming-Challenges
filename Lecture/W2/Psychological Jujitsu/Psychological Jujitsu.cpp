
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // int n;
    // cin >> n;

    vector<int> opponent_rounds;
    opponent_rounds.reserve(14);
    opponent_rounds.push_back(0);

    for (int i = 1; i < 14; i++) {
        int round;
        cin >> round;
        opponent_rounds.push_back(round);
    }

    int max_margin = 0;
    for (int i = 1; i < 14; i++) {
        int curr_margin = 0;
        for (int j = 1; j < 14; j++) {
            if (opponent_rounds[j] > i) curr_margin += 0;
            if (opponent_rounds[j] == i) curr_margin -= j;
            if (opponent_rounds[j] < i) curr_margin += j;
        }
        max_margin = max(max_margin, curr_margin);
    }

    cout << max_margin << '\n';
}