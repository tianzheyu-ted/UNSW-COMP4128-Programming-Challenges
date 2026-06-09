
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int test_case_num;
    cin >> test_case_num;

    for (int i = 0; i < test_case_num; i++) {
        int a, b;
        cin >> a;
        cin >> b;
        cout << a + b << '\n';
    }
}