
#include <vector>
#include <iostream>

using namespace std;

struct Rule {
    int x;
    int y;
    int c;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> a(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<Rule> rules(k, {-1, -1, -1});
    for (int i = 0; i < k; i++) {
        cin >> rules[i].x >> rules[i].y >> rules[i].c;
    } 

    vector<vector<long long>> dp((1 << m), vector<long long>())
}