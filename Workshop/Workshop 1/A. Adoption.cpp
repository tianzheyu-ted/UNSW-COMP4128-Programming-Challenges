
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    
    int n;
    cin >> n;

    vector<pair<int, int>> people;
    people.reserve(200000);

    for (int i = 0; i < 2 * n; i++) {
        pair<int, int> person;
        cin >> person.first;
        cin >> person.second;
        people.push_back(person);
    }

    sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
        return (a.second - a.first) > (b.second - b.first);
    });

    long long maximum_total_happiness = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (i < n) {
            maximum_total_happiness += people[i].second;
        } else {
            maximum_total_happiness += people[i].first;
        }   
    }

    cout << maximum_total_happiness << '\n';
}