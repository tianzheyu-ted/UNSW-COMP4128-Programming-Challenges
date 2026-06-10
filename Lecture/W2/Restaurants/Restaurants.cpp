
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> delegates;
    delegates.reserve(n);

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        delegates.push_back(a);
    }

    int m;
    cin >> m;

    vector<int> restaurant_capacities;
    restaurant_capacities.reserve(m);

    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        restaurant_capacities.push_back(b);
    }


    sort(delegates.begin(), delegates.end(), [] (auto& a, auto& b) {
        return a > b;
    });

    

    int starve_num = 0;
    for (int i = 0; i < n; i++) {
        int remains = delegates[i];
        sort(restaurant_capacities.begin(), restaurant_capacities.end(), [] (auto& a, auto& b) {
            return a > b;
        });

        for (int j = 0; j < m; j++) {
            if (restaurant_capacities[j] > 0 && remains > 0) {
                remains--;
                restaurant_capacities[j]--;
            }
        }

        starve_num += remains;
    }

    cout << starve_num << '\n';
}
