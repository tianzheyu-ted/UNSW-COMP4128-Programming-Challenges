// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    
    int num_animals;
    cin >> num_animals;

    int diffs[200100];
    long long total_happiness = 0;

    for (int i = 0; i < 2 * num_animals; i++) {
        int cat, dog;
        cin >> cat >> dog;

        // assume everyone gets a dog, the difference in happiness
        // is accounted for via sorting method anyway.
        total_happiness += dog;
        diffs[i] = {dog - cat};
    }
    sort(diffs, diffs + 2 * num_animals);
    // find differences of each person
    // sort out the differences towards one animal
    for (int i = 0; i < num_animals; i++) {
        total_happiness -= diffs[i];
    }
    
    cout << total_happiness << '\n';
    // the sorting will naturally tend to one animal (ala pref dog - indifferent - pref cats)
    // distribute animals to people.
    
}
