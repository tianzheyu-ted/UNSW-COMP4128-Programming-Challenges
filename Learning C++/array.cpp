

#include <vector>
#include <iostream>
using namespace std;

void print_vector(vector<int> v);

void print_2d_vector(vector<vector<int>> v);

int main(int argc, char const *argv[]) {
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    cout << "v1: ";
    print_vector(v1);
    


    vector<int> v2(10, 0);
    cout << "v2: ";
    print_vector(v2);



    vector<int> v3 = {1, 2, 3, 4};
    cout << "v3: ";
    print_vector(v3);



    v1.push_back(5);
    print_vector(v1);

    v1.pop_back();
    print_vector(v1);




    cout << v3[0] << '\n';

    cout << v3.front() << '\n';
    cout << v3.back() << '\n';

    int v3_length = v3.size();
    cout << "v3 size: " << v3_length << '\n';

    bool v3_empty = v3.empty();
    cout << "v3 empty: " << v3_empty << '\n';


    v3.resize(10);
    cout << "v3: ";
    print_vector(v3);
    cout << "v3 capacity: " << v3.capacity() << '\n';

    v3.reserve(20);
    // Need to reserve first, since if not it will assign double space for the
    // vector if it lack of space.
    cout << "v3: ";
    print_vector(v3);
    cout << "v3 capacity: " << v3.capacity() << '\n';

   


    // 2D vector
    vector<vector<int>> dp(10, vector<int>(10, -1));
    print_2d_vector(dp);

    return 0;
}


void print_vector(vector<int> v) {
    for (const auto& x : v) {
        cout << x << " ";
    }
    cout << "\n";
}

void print_2d_vector(vector<vector<int>> v) {
    for (const auto& y : v) {
        for (const auto& x : y) {
            cout << x << " ";
        }
        cout << "\n";
    }
}