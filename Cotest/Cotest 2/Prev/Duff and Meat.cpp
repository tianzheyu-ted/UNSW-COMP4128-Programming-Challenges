
#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main() {
    int n;
    cin >> n;
    
    int cost = 0;
    int lowest_price = 1e9;
    for (int i = 0; i < n; i++) {
        int a, p;
        cin >> a >> p;
        lowest_price = min(lowest_price, p);
        cost += lowest_price * a;
    }

    cout << cost;
}