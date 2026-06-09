
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    unordered_map<string, int> scores;

    scores["Alice"] = 95;
    scores["Bob"] = 92;

    for (const auto& pair : scores) {
        cout << pair.first << " got " << pair.second << '\n';
    }

    if (scores["Ted"] == 100) {
        cout << "Good job\n";
    }
    for (const auto& pair : scores) {
        cout << pair.first << " got " << pair.second << '\n';
    }

    if (scores.count("Suhan") && scores["Suhan"] == 100) {
        cout << "Good job\n";
    }
    for (const auto& pair : scores) {
        cout << pair.first << " got " << pair.second << '\n';
    }

    map<int, string> m;
    m[10] = "ten";
    m.insert({20, "twenty"});

    for (const auto& pair : m) {
        cout << pair.first << " -> " << pair.second << "\n";
    }

    if (m.count(10)) {
        cout << "key 10 exists!\n";
    }

    m.erase(20);

    for (const auto& pair : m) {
        cout << pair.first << " -> " << pair.second << "\n";
    }

    map<int, string> m2;
    m2[10] = "A";
    m2[20] = "B";
    m2[30] = "C";

    // Case 1: Find key already in map
    auto it1 = m2.lower_bound(20);
    if (it1 == m2.end()) {
        cout << "No found\n";
    } else {
        cout << "Found: m2[" << it1->first << "] = " << it1->second << '\n';
    }


    // Case 2: Find key not in map

    auto it3 = m2.upper_bound(25);
    auto it4 = m2.lower_bound(25);

    





    // auto it = m2.lower_bound(25);

    // if (it == m2.begin()) {
    //     cout << "No valid\n"
    // } else {

    // }

    return 0;
}