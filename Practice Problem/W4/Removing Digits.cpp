
#include <cmath>
#include <iostream>


using namespace std;


int main() {
    int n;
    cin >> n;

    int counter = 0;
    while (n != 0) {
        int max_digit = -1;

        int temp = n;
        while (temp > 0) {
            max_digit = max(max_digit, temp % 10);
            temp = temp / 10;
        }

        // for (int i = 0; i < 6; i++) {
        //     int temp = (int)round(pow(10, i));
        //     max_digit = max(max_digit, (n % (10 * temp)) / temp);
        // }
        
        n -= max_digit;
        counter++;
    }

    cout << counter << '\n';
}