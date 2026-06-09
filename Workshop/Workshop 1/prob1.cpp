// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    
    int test_cases;
    cin >> test_cases;


    for (int i = 0; i < test_cases; i++) {
        int string_length;
        char letter_start;
        string test_string;

        cin >> string_length;
        cin >> letter_start;
        cin >> test_string;
        

        int lastLight = -1;
        int maxGap = 0;
        for (int j = 0; j < string_length * 2; j++) {  
            if (test_string[j % string_length] == letter_start) {
                if (lastLight == -1) {
                    lastLight = j;
                }
            }

            if (test_string[j % string_length] == 'g') {
                if (j - lastLight > maxGap && lastLight != -1) {
                    maxGap = j - lastLight;
                }
                lastLight = -1;
            }
            
            
        }
        cout << maxGap << '\n';
        
    }

    
}
