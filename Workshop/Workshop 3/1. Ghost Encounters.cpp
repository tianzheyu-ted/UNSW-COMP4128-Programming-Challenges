
#include <map>
#include <vector>
#include <iostream>

using namespace std;

struct Ghost {
    int x;
    int t;
};

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> departures(n, 0);
    vector<Ghost> ghosts(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        cin >> ghosts[i].x >> ghosts[i].t;
        departures[i] = ghosts[i].t - ghosts[i].x * k;
    }

    map<int, int> data;
    for (int i = 0; i < n; i++) {
        if (data.count(departures[i])) {
            data[departures[i]] += 1;
        } else {
            data[departures[i]] = 1;
        }
    }

    pair<int, int> result = {-1, -1};
    for (auto i : data) {
        if (result.second < i.second) {
            result = i;
        }
    }

    cout << result.second << '\n';
}