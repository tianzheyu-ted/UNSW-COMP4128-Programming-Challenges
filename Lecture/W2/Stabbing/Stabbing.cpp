
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> intervals;
    for (int i = 0; i < n; i++) {
        int start, end;
        cin >> start;
        cin >> end;
        intervals.push_back({start, end});
    }

    sort(intervals.begin(), intervals.end(), [] (auto& a, auto& b) {
        return a.second < b.second;
    });

    vector<int> stabs;
    stabs.reserve(n);

    int prev_stab = -1;
    for (int i = 0; i < n; i++) {
        if (intervals[i].first > prev_stab) {
            prev_stab = intervals[i].second;
            stabs.push_back(prev_stab);
        }
    }

    for (auto& stab : stabs) {
        cout << stab << ' ';
    }

    cout << '\n' << stabs.size() << '\n';
}