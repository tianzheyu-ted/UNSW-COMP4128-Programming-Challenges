
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> activities(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        cin >> activities[i].first;
        cin >> activities[i].second;
    }

    sort(activities.begin(), activities.end(), [] (auto a, auto b) {
        return a.second < b.second;
    });

    multiset<int> room_available_time;
    for (int i = 0; i < k; i++) {
        room_available_time.insert(0);
    }

    int counter = 0;
    for (auto activitie : activities) {
        auto after_target = room_available_time.lower_bound(activitie.first);
        if (after_target != room_available_time.begin()) {
            auto target = prev(after_target);
            room_available_time.erase(target);
            room_available_time.insert(activitie.second);
            counter++;
        }
    }

    cout << counter << '\n';
}