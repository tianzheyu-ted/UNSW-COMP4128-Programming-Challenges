
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    double result = 0;
    for (int i = 1; i < n; i++) {
        result += (double) n / (double) (n - i);
    }

    printf("%.12f\n", result);
}