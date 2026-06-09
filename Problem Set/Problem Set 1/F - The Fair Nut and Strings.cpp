
#include <iostream>

using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    string s, t;
    cin >> s >> t;

    long long diff = 0;
    long long total_c = 0; 

    for (int i = 0; i < n; i++) {
        diff = diff * 2 + (t[i] - s[i]);

        long long current_level_nodes = diff + 1;

        if (current_level_nodes >= k) {
            total_c += (long long)(n - i) * k;
            break; 
        } else {
            total_c += current_level_nodes;
        }
    }

    cout << total_c << '\n';
}