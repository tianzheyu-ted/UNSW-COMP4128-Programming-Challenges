
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<tuple<long long, long long ,int>> stars(n);
    for (int i = 0; i < n; i++) {
        cin >> get<0>(stars[i]) >> get<1>(stars[i]);
        get<2>(stars[i]) = i + 1;
    }

    sort(stars.begin(), stars.end(), [] (auto& a, auto& b) {
        if (get<0>(a) == get<0>(b)) {
            return get<1>(a) < get<1>(b);
        }
        return get<0>(a) < get<0>(b);
    });

    auto a = stars[0];
    auto b = stars[1];
    for (int i = 2; i < n; i++) {
        auto c = stars[i];
        if ((get<1>(a) - get<1>(b)) * (get<0>(c) - get<0>(b)) != (get<1>(c) - get<1>(b)) * (get<0>(a) - get<0>(b))) {
            cout << get<2>(a) << ' ' << get<2>(b) << ' ' << get<2>(c) << '\n';
            return 0;
        }
    }
}