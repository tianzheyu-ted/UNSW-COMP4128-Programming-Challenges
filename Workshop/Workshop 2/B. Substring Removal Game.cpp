
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {

    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        string str;
        cin >> str;

        int index = 0;
        vector<pair<bool, int>> v;
        v.reserve(str.size());
        v.push_back({(str[0] == '1'), 1});

        for (int j = 1; j < str.size(); j++) {
            if (str[j] == str[j - 1]) {
                v[index].second++;
            } else {
                v.push_back({(str[j] == '1'), 1});
                index++;
            }
        }

        sort(v.begin(), v.end(), greater<pair<bool, int>>());

        int alice_score = 0;
        for (int j = 0; j < v.size(); j += 2) {
            if (v[j].first) {
                alice_score += v[j].second;
            } else {
                break;
            }
        }

        cout << alice_score << '\n';
    }
}