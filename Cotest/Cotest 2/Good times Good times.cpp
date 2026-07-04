
#include <set>
#include <cmath>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

bool check(long long n);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    // vector<long long> good_y;
    // good_y.reserve(10000);

    // for (long long i = 2; i < round(pow(10, 9)); i++) {
    //     if (check(i)) {
    //         good_y.push_back(i);
    //     }
    // }


    set<long long> good_set;


    for (int d1 = 0; d1 <= 9; d1++) {
        for (int d2 = d1; d2 <= 9; d2++) {
            
            queue<long long> q;
            if (d1 > 0) q.push(d1);
            if (d2 > 0 && d1 != d2) q.push(d2);

            while (!q.empty()) {
                long long curr = q.front();
                q.pop();

                if (curr >= 2 && curr <= 1000000000LL) {
                    good_set.insert(curr);
                }

                if (curr <= 100000000LL) {
                    q.push(curr * 10 + d1);
                    if (d1 != d2) {
                        q.push(curr * 10 + d2);
                    }
                }
            }
        }
    }

    vector<long long> good_y(good_set.begin(), good_set.end());

    for (int i = 0; i < t; i++) {
        long long x;
        cin >> x;

        for (auto y : good_y) {
            if (check(x * y)) {
                cout << y << '\n';
                break;
            }
        }

        // vector<int> digits;
        // digits.reserve(7);

        // set<int> s;

        // bool start = false;
        // for (int i = 7; i >= 0; i--) {
        //     int digit = x % (int) round(pow(10, i));
        //     if (digit && !start) {
        //         digits.push_back(digit);
        //         s.insert(digit);
        //         start = true;
        //     }   
        // }
    }
}

bool check(long long n) {
    int mask = 0;
    int count = 0;
    
    while (n > 0) {
        int digit = n % 10;
        if ((mask & (1 << digit)) == 0) {
            mask |= (1 << digit);
            count++;
            if (count > 2) return false;
        }
        n /= 10;
    }
    return true;
}