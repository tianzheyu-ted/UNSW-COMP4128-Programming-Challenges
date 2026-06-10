
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool check_x(long long x, vector<int>& tastiness, int k);

int main() {
    int n, k;
    cin >> n;
    cin >> k;

    vector<int> tastiness;
    tastiness.reserve(n);

    long long total_tastiness = 0;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        total_tastiness += t;
        tastiness.push_back(t);
    }

    long long lo = 0;
    long long hi = total_tastiness;
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        if (check_x(mid, tastiness, k)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << '\n';
}

bool check_x(long long x, vector<int>& tastiness, int k) {
    long long curr_sum = 0;
    int child_cover = 0;
    for (int i = 0; i < tastiness.size(); i++) {
        curr_sum += tastiness[i];
        if (curr_sum >= x) {
            child_cover++;
            curr_sum = 0;
        }
    }
    return child_cover >= k;
}