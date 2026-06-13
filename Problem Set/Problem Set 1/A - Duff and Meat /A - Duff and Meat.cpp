
#include <iostream>
using namespace std;

int main() {
    int num_of_days;
    cin >> num_of_days;

    int total_money_need = 0;
    int lowest_price = 101;

    for (int i = 0; i < num_of_days; i++) {
        int meat_need, meat_price;
        cin >> meat_need;
        cin >> meat_price;

        if (lowest_price > meat_price) {
            lowest_price = meat_price;
        }

        total_money_need += lowest_price * meat_need;
    }

    cout << total_money_need << '\n';
}