
#include <vector>
#include <iostream>

using namespace std;

int rectangle(int r, int c, int h, int w, vector<vector<int>>& q);
bool check(int x, int r, int c, int h, int w, vector<vector<int>>& q);

int main() {
    int r, c, h, w;
    cin >> r >> c >> h >> w;

    vector<vector<int>> q(r, vector<int>(c, 0));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> q[i][j];
        }
    }

    cout << rectangle(r, c, h, w, q) << '\n';
}

int rectangle(int r, int c, int h, int w, vector<vector<int>>& q) {
    int lo = 1;
    int hi = r * c;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid, r, c, h, w, q)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return lo;
}


bool check(int x, int r, int c, int h, int w, vector<vector<int>>& q) {
    vector<vector<int>> prefix(r + 1, vector<int>(c + 1, 0));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int curr = 0;
            if (q[i][j] < x) {
                curr = -1;
            } else if (q[i][j] > x) {
                curr = 1;
            }
            prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + curr;
        }
    }

    for (int i = 0; i < r - h + 1; i++) {
        for (int j = 0; j < c - w + 1; j++) {
            int sum = prefix[i + h][j + w] - prefix[i + h][j] - prefix[i][j + w] + prefix[i][j];
            if (sum <= 0) {
                return true;
            }
        }
    }

    return false;
}