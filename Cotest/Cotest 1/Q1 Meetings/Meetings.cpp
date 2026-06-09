
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int n;
    cin >> n;

    vector<pair<int, int>> meetings;
    meetings.reserve(n);

    for (int i = 0; i < n; i++) {
        int s, e;
        cin >> s;
        cin >> e;

        pair<int, int> meeting(s, e);
        meetings.push_back(meeting);
    }

    sort(meetings.begin(), meetings.end());

    for (int i = 1; i < n; i++) {
        if (meetings[i - 1].second > meetings[i].first) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";
}