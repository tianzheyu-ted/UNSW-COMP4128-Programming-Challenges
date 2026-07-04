
#include<queue>
#include <iostream>

using namespace std;

int main() {
    int n, t;
    cin >> n >> t;

    deque<int> dq;
    int time_left = t;
    int max_book_num = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a > time_left) {
            while (dq.size() > 0) {
                time_left += dq.front();
                dq.pop_front();
                if (time_left >= a) {
                    dq.push_back(a);
                    time_left -= a;
                    break;
                }
            }
        } else {
            dq.push_back(a);
            time_left -= a;
            max_book_num = max(max_book_num, (int)dq.size());
        }
    }

    cout << max_book_num << '\n';
}