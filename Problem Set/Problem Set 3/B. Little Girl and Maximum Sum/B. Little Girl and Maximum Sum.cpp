
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct Frequency {
    int freq;
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> array(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    vector<int> diff(n + 2, 0);
    vector<pair<int, int>> queries(q, {-1, -1});
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
        diff[queries[i].first]++;
        diff[queries[i].second + 1]--;
    }

    int current_freq = 0;
    vector<Frequency> freqs(n, {0});
    for (int i = 1; i < n + 1; i++) {
        current_freq += diff[i];
        freqs[i - 1].freq = current_freq; 
    }

    sort(freqs.begin(), freqs.end(), [] (auto& a, auto& b) {
        return a.freq > b.freq;
    });

    sort(array.begin(), array.end(), [] (auto& a, auto& b) {
        return a > b;
    });

    long long result = 0;
    for (int i = 0; i < n; i++) {
        result += (long long)freqs[i].freq * (long long)array[i];
    }

    cout << result << '\n';
}