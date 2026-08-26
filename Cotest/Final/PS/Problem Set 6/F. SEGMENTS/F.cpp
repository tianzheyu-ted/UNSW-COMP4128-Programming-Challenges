#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    long long a, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Segment> segs(n);
    for (int i = 0; i < n; ++i) {
        long long a, b, h;
        cin >> a >> b >> h;
        segs[i] = {a, b};
    }

    int max_r = 1;

    for (int i = 0; i < n; ++i) {
        vector<Segment> inside;

        for (int j = 0; j < n; ++j) {
            if (segs[i].a <= segs[j].a && segs[j].b <= segs[i].b) {
                inside.push_back(segs[j]);
            }
        }

        sort(inside.begin(), inside.end(), [](const Segment& x, const Segment& y) {
            return x.b < y.b;
        });

        int count = 0;
        long long last_end = -4000000000LL;
        
        for (const auto& s : inside) {
            if (s.a >= last_end) {
                count++;
                last_end = s.b;
            }
        }
        
        max_r = max(max_r, count);
    }

    cout << max_r << "\n";

    return 0;
}
