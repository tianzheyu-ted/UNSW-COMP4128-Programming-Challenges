
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> qualifications(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> qualifications[i];
    }

    int m;
    cin >> m;
    vector<long long> min_in_cost(n + 1, 1e18);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        min_in_cost[b] = min(min_in_cost[b], (long long) c);
    }
    
    long long total_cost = 0;
    int root_count = 0;

    for (int i = 1; i <= n; i++) {
        if (min_in_cost[i] == 1e18) {
            root_count++;
        } else {
            total_cost += min_in_cost[i];
        }
    }
    
    if (root_count > 1) {
        cout << -1 << '\n';
    } else {
        cout << total_cost << '\n';
    }
}