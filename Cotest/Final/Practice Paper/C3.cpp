
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Item {
    int id;
    long long price, time;
    long long last_sold;
    bool operator<(const Item& o) const {
        return id < o.id;
    };
};

int main() {
    int n, m;
    cin >> n >> m;

    // item{ price, crafting time }
    vector<Item> items(n, {-1, -1, -1, -1});
    for (int i = 0; i < n; i++) {
        cin >> items[i].price >> items[i].time;
        items[i].id = i + 1;
    }
    
    // customers{ visit date, budget }
    vector<pair<long long, long long>> customers(m, {-1, -1});
    for (int i = 0; i < m; i++) {
        cin >> customers[i].first >> customers[i].second;
    }

    sort(items.begin(), items.end(), [] (auto& a, auto& b) {
        return a.price > b.price;
    });

    for (int i = 0; i < m; i++) {
        long long date = customers[i].first;
        bool buy = false;
        for (auto& item : items) {
            if (date >= item.last_sold + item.time || item.last_sold == -1) {
                cout << item.id << ' ';
                item.last_sold = date;
                buy = true;
                break;
            }
        }
        if (!buy) {
            cout << 0 << ' ';
        }
    }

    cout << '\n';
}