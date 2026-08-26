
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

long long ask_area(int i, int j, int k) {
    cout << "1 " << i << " " << j << " " << k << endl;
    long long res;
    cin >> res;
    return res;
}

int ask_sign(int i, int j, int k) {
    cout << "2 " << i << " " << j << " " << k << endl;
    int res;
    cin >> res;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int x = 2;
    for (int i = 3; i <= n; ++i) {
        int sign = ask_sign(1, x, i);
        if (sign == -1) {
            x = i;
        }
    }

    vector<long long> area(n + 1, 0); 
    int y = -1;
    long long max_area = -1;
    
    for (int i = 2; i <= n; ++i) {
        if (i == x) continue;
        area[i] = ask_area(1, x, i);
        if (area[i] > max_area) {
            max_area = area[i];
            y = i;
        }
    }

    vector<int> s1, s2;
    for (int i = 2; i <= n; ++i) {
        if (i == x || i == y) continue;
        int sign = ask_sign(1, y, i);
        if (sign == -1) {
            s1.push_back(i);
        } else {
            s2.push_back(i);
        }
    }

    sort(s1.begin(), s1.end(), [&](int a, int b) {
        return area[a] < area[b];
    });
    
    sort(s2.begin(), s2.end(), [&](int a, int b) {
        return area[a] > area[b];
    });

    vector<int> ans;
    ans.push_back(1);
    ans.push_back(x);
    for (int p : s1) ans.push_back(p);
    ans.push_back(y);
    for (int p : s2) ans.push_back(p);

    cout << "0";
    for (int p : ans) {
        cout << " " << p;
    }
    cout << endl;
}