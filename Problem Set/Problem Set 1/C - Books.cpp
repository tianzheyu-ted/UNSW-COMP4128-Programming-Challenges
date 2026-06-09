
#include <deque>
#include <iostream>
using namespace std;

int main() {
    int n, t;
    cin >> n;
    cin >> t;

    deque<int> window;
    
    int time_left = t;
    int max_num_book = 0;

    for (int i = 0; i < n; i++) {
        int time_require;
        cin >> time_require;

        if (time_left >= time_require) {
            window.push_back(time_require);
            if (max_num_book < window.size()) {
                max_num_book = window.size();
            }
            time_left -= time_require;
        } else {
            while (window.size() > 0 && time_left < time_require) {
                time_left += window.front();
                window.pop_front();
            }

            if (time_left < time_require) continue;

            window.push_back(time_require);
            time_left -= time_require;
            if (max_num_book < window.size()) {
                max_num_book = window.size();
            }
        }
    }

    if (max_num_book < window.size()) {
        max_num_book = window.size();
    }

    cout << max_num_book << '\n';
}