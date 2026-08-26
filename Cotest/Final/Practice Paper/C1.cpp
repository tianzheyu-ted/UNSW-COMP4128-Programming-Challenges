
#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // item{ price, crafting time }
    set<long long> prices;
    map<long long, long long> priceToId;
    vector<pair<long long, long long>> items(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        cin >> items[i].first >> items[i].second;
        prices.insert(items[i].first);
        priceToId[items[i].first] = i + 1;
    }
    
    // customers{ visit date, budget }
    vector<pair<long long, long long>> customers(m, {-1, -1});

    for (int i = 0; i < m; i++) {
        cin >> customers[i].first >> customers[i].second;
        auto it = prices.lower_bound(customers[i].second);
        if (it != prices.end() && *it == customers[i].second) {
            cout << priceToId[*it] << ' ';
        } else if (it == prices.begin()) {
            cout << 0 << ' ';
        } else {
            cout << priceToId[*prev(it)] << ' ';
        }
    }

    cout << '\n';
}