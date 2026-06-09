
#include <vector>
#include <iostream>
using namespace std;

int main() {

    int num_test_cases;
    cin >> num_test_cases;

    for (int i = 0; i < num_test_cases; i++) {
        int num_elements;
        cin >> num_elements;
        
        int prev = 0;
        long long result = 0;
        int current_biggest = 0;
        for (int j = 0; j < num_elements; j++) {
            int num;
            cin >> num;
            
            if (prev == 0) {
                prev = num;
                current_biggest = num;
            } else {
                if ((prev < 0 && num < 0) || (prev > 0 && num > 0)) {
                    if (num > current_biggest) {
                        current_biggest = num;
                    }
                } else {
                    result += current_biggest;
                    prev = num;
                    current_biggest = num;
                }
            }
        }
        result += current_biggest;
        cout << result << '\n';
    }
}