
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
    int n, k;
    cin >> n;
    cin >> k;

    vector<pair<int, int>> activities(n);
    for (int i = 0; i < n; i++) {
        int s, f;
        cin >> s;
        cin >> f;
        activities[i] = {s, f};
    }

    sort(activities.begin(), activities.end(), [] (auto& a, auto&b) {
        if (a.second == b.second) {
            return a.first < b.first;
        } 
        return a.second < b.second;
    });

    multiset<int> rooms;
    for (int i = 0; i < k; i++) rooms.insert(-1);

    int result = 0;
    // vector<int> rooms_available_after(k, -1);
    for (int i = 0; i < n; i++) {
        int start_time = activities[i].first;
        int finish_time = activities[i].second;

        // int room_id = -1;
        // int latest_room_available_after = -2;
        // for (int j = 0; j < k; j++) {
        //     if (rooms_available_after[j] < start_time) {
        //         if (latest_room_available_after < rooms_available_after[j]) {
        //             room_id = j;
        //             latest_room_available_after = rooms_available_after[j];
        //         }
        //     }
        // }

        // if (room_id != -1) {
        //     rooms_available_after[room_id] = finish_time;
        //     result++;
        // }


        auto iterator = rooms.lower_bound(start_time);
        if (iterator != rooms.begin()) {
            rooms.erase(prev(iterator));
            rooms.insert(finish_time);
            result++;
        }
    }

    cout << result << '\n';
}