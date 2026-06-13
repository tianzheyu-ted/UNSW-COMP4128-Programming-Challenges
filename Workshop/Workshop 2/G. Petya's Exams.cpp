
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Exam {
    int id;
    int s;
    int d;
    int c;
};


int main() {
    int n, m;
    cin >> n;
    cin >> m;

    vector<int> result(n + 1, 0);
    vector<Exam> exams(m + 1);

    for (int i = 1; i <= m; i++) {
        int s, d, c;
        cin >> s;           // the day when the questions of exam will be given
        cin >> d;           // the day of the exam
        cin >> c;           // number of days needs to prepare for the exam
        exams[i] = {i, s, d, c};
        result[d] = i;
    }

    for (int i = 1; i <= n; i++) {
        if (result[i]) {
            if (exams[result[i]].c > 0) {
                cout << -1 << '\n';
                return 0;
            }
            result[i] = m + 1;
        } else {
            int exam_id = -1;
            int earliest_deadline = 1e9;
            for (int j = 1; j <= m; j++) {
                if (exams[j].s <= i && exams[j].c > 0) {
                    if (exams[j].d < earliest_deadline) {
                        earliest_deadline = exams[j].d;
                        exam_id = j;
                    }
                }
            }

            if (exam_id != -1) {
                result[i] = exam_id;
                exams[exam_id].c--;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << result[i] << ' ';
    }

    cout << '\n';
}