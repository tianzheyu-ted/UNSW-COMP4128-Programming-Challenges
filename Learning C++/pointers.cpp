
#include <iostream>
using namespace std;

void add_one_c(int* num);
void add_one_cpp(int& num);

int main() {
    int x = 100;
    int* p = &x;
    cout << x << '\n';

    add_one_c(p);
    cout << x << '\n';

    add_one_cpp(x);
    cout << x << '\n';
}

void add_one_c(int* num) {
    *num = *num + 1;
}

void add_one_cpp(int& num) {
    num = num + 1;
}