
#include <set>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> qualifications(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> qualifications[i];
    }

    vector<int> best_supervisor_cost(n, 1e9);

    int m;
    cin >> m;
    
    // (surbodinate : b) --c--> (a : supervisor)
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        best_supervisor_cost[b - 1] = min(c, best_supervisor_cost[b - 1]);
    }

    int counter = 0;
    long long cost = 0;
    for (int i = 0; i < n; i++) {
        if (best_supervisor_cost[i] != 1e9) {
            cost += best_supervisor_cost[i];
        } else {
            counter++;
        }
    }

    if (counter > 1) {
        cout << -1 << '\n';
    } else {
        cout << cost << '\n';
    }
}