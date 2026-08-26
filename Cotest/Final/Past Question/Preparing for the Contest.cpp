#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


struct Student {
    int id;
    long long b;
    long long c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long s;
    if (!(cin >> n >> m >> s)) return 0;

    vector<pair<long long, int>> bugs(m);
    for (int i = 0; i < m; i++) {
        cin >> bugs[i].first;
        bugs[i].second = i;
    }

    vector<Student> students(n);
    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        cin >> students[i].b;
    }
    for (int i = 0; i < n; i++) {
        cin >> students[i].c;
    }

    sort(bugs.begin(), bugs.end(), [](const auto& x, const auto& y) {
        return x.first > y.first;
    });

    sort(students.begin(), students.end(), [](const auto& x, const auto& y) {
        return x.b > y.b;
    });

    vector<int> best_assignment(m, 0);

    auto check = [&](int d) -> bool {
        long long current_cost = 0;
        vector<int> assignment(m, 0);
        
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        
        int student_idx = 0;
    
        for (int i = 0; i < m; i += d) {
            long long req_complexity = bugs[i].first;
            
            while (student_idx < n && students[student_idx].b >= req_complexity) {
                pq.push({students[student_idx].c, students[student_idx].id});
                student_idx++;
            }

            if (pq.empty()) return false;
            
            auto best_student = pq.top();
            pq.pop(); 
            
            current_cost += best_student.first;
            if (current_cost > s) return false;
            
            for (int j = i; j < min(m, i + d); j++) {
                assignment[bugs[j].second] = best_student.second;
            }
        }
        
        best_assignment = assignment;
        return true;
    };


    int lo = 1, hi = m, ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    if (ans == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 0; i < m; i++) {
            cout << best_assignment[i] << (i == m - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}