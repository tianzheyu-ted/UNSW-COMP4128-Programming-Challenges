
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<long long, long long>> activities(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        cin >> activities[i].first >> activities[i].second;
    }

    sort(activities.begin(), activities.end(), [] (auto& a, auto& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });

    multiset<long long> rooms;
    for (int i = 0; i < k; i++) {
        rooms.insert(0);
    }

    int counter = 0;
    for (auto activity : activities) {
        // find first value >= start
        auto it = rooms.lower_bound(activity.first);
        if (it != rooms.begin()) {
            auto room = prev(it);
            rooms.erase(room);
            rooms.insert(activity.second);
            counter++;
        }
    }

    cout << counter << '\n';
}