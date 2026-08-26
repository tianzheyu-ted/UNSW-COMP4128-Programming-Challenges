
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    long long t;

    cin >> n >> t;

    deque<int> q;

    int max_book_num = 0;
    int book_counter = 0;
    long long time_left = t;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        while (time_left < a && !q.empty()) {
            time_left += q.front();
            q.pop_front();
            book_counter--;
        }

        if (time_left >= a) {
            time_left -= a;
            q.push_back(a);
            book_counter++;
            max_book_num = max(max_book_num, book_counter);
        }
    }

    cout << max_book_num << '\n';
}