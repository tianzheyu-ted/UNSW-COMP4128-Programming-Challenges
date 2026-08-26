
#include <set>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    multiset<long long> prefix;
    multiset<long long> suffix;
    vector<long long> array(n, 0);

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> array[i];
        sum += array[i];
        suffix.insert(array[i]);
    }

    if (sum % 2 == 1) {
        cout << "NO\n";
        return 0;
    }


    long long half = sum / 2;
    long long current_sum = 0;

    for (int i = 0; i < n; i++) {
        current_sum += array[i];
        prefix.insert(array[i]);
        suffix.erase(suffix.find(array[i]));
        
        if (current_sum < half) {
            if (suffix.count(half - current_sum)) {
                cout << "YES\n";
                return 0;
            }
        } else if (current_sum == half) {
            cout << "YES\n";
            return 0;
        } else if (current_sum > half) {
            if (prefix.count(current_sum - half)) {
                cout << "YES\n";
                return 0;
            }
        }
    }

    cout << "NO\n";
    return 0;
}