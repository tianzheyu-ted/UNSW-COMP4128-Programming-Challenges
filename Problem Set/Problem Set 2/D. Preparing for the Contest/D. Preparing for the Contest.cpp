
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Student {
    long long id;
    long long level;
    long long reward;

    bool operator<(const Student& other) const {
        if (level == other.level) {
            return reward < other.reward;
        }
        return level < other.level;
    }
};

struct Bug {
    long long id;
    long long complexity;
    long long done_by;
};

bool check_x_days(long long x, vector<Bug>& bugs, vector<Student>& students, long long s, long long n);

int main() {
    long long n, m ,s;
    cin >> n;
    cin >> m;
    cin >> s;

    vector<Bug> bugs(m, {0, 0, 0});
    for (long long i = 0; i < m; i++) {
        bugs[i].id = i;
        cin >> bugs[i].complexity;
    }

    long long highest_level = 0;
    vector<Student> students(n, {0, 0, 0});
    for (long long i = 0; i < n; i++) {
        students[i].id = i + 1;
        cin >> students[i].level;
        highest_level = max(highest_level, students[i].level);
    }   
    for (long long i = 0; i < n; i++) {
        cin >> students[i].reward;
    }

    
    sort(bugs.begin(), bugs.end(), [] (auto& a, auto& b) {
        return a.complexity > b.complexity;
    });

    sort(students.begin(), students.end(), [] (auto& a, auto& b) {
        if (a.level == b.level) {
            return a.reward < b.reward;
        }
        return a.level > b.level;
    });


    long long lo = 1;
    long long hi = m;

    if (!check_x_days(hi, bugs, students, s, n)) {
        cout << "NO\n";
        return 0;
    } else {
        cout << "YES\n";
    }

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (check_x_days(mid, bugs, students, s, n)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    long long num_days = lo;

    check_x_days(num_days, bugs, students, s, n);

    sort(bugs.begin(), bugs.end(), [] (auto& a, auto& b) {
        return a.id < b.id;
    });

    for (long long i = 0; i < m; i++) {
        cout << bugs[i].done_by << ' ';
    }

    cout << '\n';
}

struct CompareReward {
    bool operator()(const Student& a, const Student& b) const {
        return a.reward > b.reward;
    }
};


bool check_x_days(long long x, vector<Bug>& bugs, vector<Student>& students, long long s, long long n) {
    priority_queue<Student, vector<Student>, CompareReward> pq;

    long long student_index = 0;
    long long total_given_passes = 0;
    for (long long i = 0; i < bugs.size(); i += x) {
        long long hardest_complexity = bugs[i].complexity;

        while (student_index < n && students[student_index].level >= hardest_complexity) {
            pq.push(students[student_index]);
            student_index++;
        }

        if (pq.empty()) return false;

        Student best_student = pq.top();
        pq.pop();

        for (long long j = i; j < i + x && j < bugs.size(); j++) {
            bugs[j].done_by = best_student.id;
        }

        total_given_passes += best_student.reward;
        if (total_given_passes > s) return false;
    }

    return true;
}



int main_attempt_1() {
    long long n, m ,s;
    cin >> n;
    cin >> m;
    cin >> s;

    vector<Bug> bugs(m, {0, 0, 0});
    for (long long i = 0; i < m; i++) {
        bugs[i].id = i;
        cin >> bugs[i].complexity;
    }

    long long highest_level = 0;
    vector<Student> students(n + 1, {0, 0, 0});
    for (long long i = 1; i < n + 1; i++) {
        students[i].id = i;
        cin >> students[i].level;
        highest_level = max(highest_level, students[i].level);
    }   
    for (long long i = 1; i < n + 1; i++) {
        cin >> students[i].reward;
    }

    multiset<Student> students_available;
    multiset<Student> students_not_available;
    for (long long i = 1; i < n + 1; i++) {
        students_available.insert(students[i]);
    }

    sort(bugs.begin(), bugs.end(), [] (auto& a, auto& b) {
        return a.complexity > b.complexity;
    });

    long long total_given_passes = 0;
    for (long long i = 0; i < m; i++) {
        long long level_required = bugs[i].complexity;

        if (level_required > highest_level) {
            cout << "NO\n";
            return 0;
        }

        auto iterator = students_available.lower_bound(Student{0, level_required, 0});

        if (iterator == students_available.end()) continue;

        Student student = *iterator;

        bugs[i].done_by = student.id;

        total_given_passes += student.reward;
        if (total_given_passes > s) {
            cout << "NO\n";
            return 0;
        }

        students_available.erase(students_available.find(student));
        students_not_available.insert(student);
    }
}