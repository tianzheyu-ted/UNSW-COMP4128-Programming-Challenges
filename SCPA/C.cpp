
#include <set>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> children(n, vector<int>());
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        children[parent - 1].push_back(i);
    }

    set<int> broken;
    for (int i = 1; i <= k; i++) {
        int a;
        cin >> a;
        broken.insert(a);
    }

    int result = 0; 

    auto post_order_travers = [&] (auto& self, int curr) -> int {
        if (children[curr].empty()) {
        if (broken.count(curr)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        int counter = 0;
        for (auto next : children[curr]) {

            if (self(self, next)) { 
                counter++;
            }
        }

        if (counter >= 2) {
            result--; 
            return 0; 
        } 
        else if (counter == 1) {
            return 1; 
        } 
        else {
            if (broken.count(curr)) {
                result++; 
                return 1;
            } else {
                return 0;
            }
        }
    }
    };

    post_order_travers(post_order_travers, 0);

    cout << result << '\n';
}