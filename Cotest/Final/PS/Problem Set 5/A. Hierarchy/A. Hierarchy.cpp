
#include <vector>
#include <iostream>

using namespace std;

struct Employee {
    int qualification;
    int min_cost_in_edge;
    vector<int> in;
    vector<int> out;
};

struct Application {
    int a;
    int b;
    int c;
};

int main() {
    int n;
    cin >> n;

    vector<Employee> employees(n, {-1, 1000000000, {}, {}});
    for (int i = 0; i < n; i++) {
        cin >> employees[i].qualification;
    }

    int m;
    cin >> m;

    vector<Application> applications(m, {-1, -1, -1});
    for (int i = 0; i < m; i++) {
        cin >> applications[i].a >> applications[i].b >> applications[i].c;
        employees[applications[i].a - 1].out.push_back(i);
        employees[applications[i].b - 1].in.push_back(i);
        employees[applications[i].b - 1].min_cost_in_edge = min(employees[applications[i].b - 1].min_cost_in_edge, applications[i].c);
    }

    int cost = 0;
    int counter = 0;
    for (auto employee : employees) {
        if (employee.in.size() == 0) {
            counter++;
        } else {
            cost += employee.min_cost_in_edge;
        }
    }

    if (counter > 1) {
        cout << -1 << '\n';
        return 0;
    }

    cout << cost << '\n';
}