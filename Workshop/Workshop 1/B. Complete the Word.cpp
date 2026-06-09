
#include <set>
#include <vector>
#include <iostream>

using namespace std;


int main() {
    string str;
    cin >> str;

    if (str.size() < 26) {
        cout << -1 << '\n';
        return 0;
    }

    bool found = false;

    for (int i = 0; i <= str.size() - 26; i++) {
        bool valid = true;
        int question_mark_count = 0;
        vector<int> counters(26, 0);

        for (int j = i; j < i + 26; j++) {
            if (str[j] == '?') {
                question_mark_count += 1;
                continue;
            }

            counters[str[j] - 'A'] += 1;
            if (counters[str[j] - 'A'] > 1) {
                valid = false;
                break;
            }
        }

        if (valid) {
            int sum = 0;
            set<char> letters_to_add;
            for (int j = 0; j < 26; j++) {
                sum += counters[j];
                if (counters[j] == 0) {
                    letters_to_add.insert('A' + j);
                }
            }

            if (sum + question_mark_count == 26) {
                for (int j = i; j < i + 26; j++) {
                    if (str[j] == '?') {
                        str[j] = *letters_to_add.begin();
                        letters_to_add.erase(str[j]);
                    }
                }
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '?') {
            str[i] = 'A';
        }
    }

    cout << str << '\n';
}