
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Bug {
    int id;
    long long complexity;
};

struct Student {
    int id;
    long long ability;
    long long cost;
};

struct MyCmp {
    bool operator()(const Student& a, const Student& b) const {
        if (a.cost != b.cost) return a.cost < b.cost; 
        return a.id < b.id;
    }
};


struct MyCmp2 {
    bool operator()(const Student& a, const Student& b) const {
        if (a.ability != b.ability) return a.ability > b.ability; 
        return a.id < b.id;
    }
};


bool check(int x, vector<Bug>& bugs, vector<Student> source_students, long long s, vector<int>& record);

int main() {
    int n, m;
    long long s;
    cin >> n >> m >> s;

    vector<Bug> bugs(m, {-1, -1});
    for (int i = 0; i < m; i++) {
        bugs[i].id = i;
        cin >> bugs[i].complexity;
    }

    sort(bugs.begin(), bugs.end(), [] (auto& a, auto& b) {
        return a.complexity > b.complexity;
    });


    vector<Student> students(n, {-1, -1, -1});
    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        cin >> students[i].ability;
    }
    for (int i = 0; i < n; i++) {
        cin >> students[i].cost;
    }

    multiset<Student, MyCmp2> students_set(students.begin(), students.end());

    int lo = 1;
    int hi = m;
    vector<int> record(m, -1);

    if (!check(m, bugs, students, s, record)) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid, bugs, students, s, record)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    check(lo, bugs, students, s, record);

    for (auto item : record) {
        cout << item << ' ';
    }

    cout << '\n';
}

bool check(int x, vector<Bug>& bugs, vector<Student> source_students, long long s, vector<int>& record) {
    auto cmp_ability = [](const Student& a, const Student& b) {
        if (a.ability != b.ability) return a.ability > b.ability;
        return a.id < b.id;
    };
    auto cmp_cost = [](const Student& a, const Student& b) {
        if (a.cost != b.cost) return a.cost < b.cost;
        return a.id < b.id;
    };

    multiset<Student, decltype(cmp_ability)> students_by_ability(source_students.begin(), source_students.end(), cmp_ability);
    multiset<Student, decltype(cmp_cost)> pool_by_cost(cmp_cost);

    long long budget_left = s;
    int m = bugs.size();

    for (int i = 0; i < m; i += x) {
        long long max_complexity_needed = bugs[i].complexity;

        while (!students_by_ability.empty() && students_by_ability.begin()->ability >= max_complexity_needed) {
            pool_by_cost.insert(*students_by_ability.begin());
            students_by_ability.erase(students_by_ability.begin());
        }

        if (pool_by_cost.empty()) return false;

        Student best_student = *pool_by_cost.begin();
        pool_by_cost.erase(pool_by_cost.begin());

        budget_left -= best_student.cost;
        if (budget_left < 0) return false;

        for (int j = i; j < min(i + x, m); j++) {
            record[bugs[j].id] = best_student.id;
        }
    }
    return true;
}

bool check_old(int x, vector<Bug>& bugs, multiset<Student, MyCmp2> students_set, long long s, vector<int>& record) {
    int counter = 0;
    long long budget_left = s;
    for (int i = 0; i < bugs.size(); i += x) {
        auto it = students_set.upper_bound({1000000, bugs[i].complexity, 0});
        if (it == students_set.begin()) return false;
        auto temp = multiset<Student, MyCmp>(students_set.begin(), it);
        Student student = *temp.begin();
        if (student.cost > budget_left) return false;
        budget_left -= student.cost;
        students_set.erase(students_set.find(student));
        
        for (int j = i; j < min(i + x, (int)bugs.size()); j++) {
            record[bugs[j].id] = student.id;
            counter++;
        }
    }

    return true;
}