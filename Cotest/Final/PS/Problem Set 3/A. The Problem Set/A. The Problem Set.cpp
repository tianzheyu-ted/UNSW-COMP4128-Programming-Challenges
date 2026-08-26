
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    int range_start;
    int range_end;
    int max;
    long long sum;
    bool is_inc;
    bool is_dec;
    int first_val;
    int last_val;
    int left;
    int right;
};

struct QueryResult {
    int max;
    long long sum;
    bool is_inc;
    bool is_dec;
    int first_val;
    int last_val;
};

int build(int start, int end, vector<int>& problems, vector<Node>& range_tree);
void update(int x, int new_value, int root_index, vector<Node>& range_tree);
QueryResult search(int start, int end, int root_index, vector<Node>& range_tree);

int main() {
    int n = 0, m = 0;
    if (!(cin >> n >> m)) {
        return 0;
    }
    
    if (n <= 0) {
        return 0; 
    }

    vector<int> problems(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> problems[i];
    }

    vector<Node> range_tree;
    range_tree.reserve(4 * n);
    int root_index = build(0, n - 1, problems, range_tree);

    for (int i = 0; i < m; i++) {
        char type;
        int x, y;
        cin >> type >> x >> y;
        
        if (type == 'U') {
            update(x - 1, y, root_index, range_tree);
            // cout << y << '\n';
        } else if (type == 'M') {
            cout << search(x - 1, y - 1, root_index, range_tree).max << '\n';
        } else if (type == 'S') {
            cout << search(x - 1, y - 1,root_index, range_tree).sum << '\n';
        } else if (type == 'I') {
            cout << search(x - 1, y - 1, root_index, range_tree).is_inc << '\n';
        } else if (type == 'D') {
            cout << search(x - 1, y - 1, root_index, range_tree).is_dec << '\n';
        }
    }
}


int build(int start, int end, vector<int>& problems, vector<Node>& range_tree) {
    int current_index = range_tree.size();
    range_tree.push_back({start, end, 0, 0, false, false, -1, -1, -1, -1});

    if (start == end) {
        range_tree[current_index].max = problems[start];
        range_tree[current_index].sum = problems[start];
        range_tree[current_index].first_val = problems[start];
        range_tree[current_index].last_val = problems[start];
        range_tree[current_index].is_dec = true;
        range_tree[current_index].is_inc = true;
        return current_index;
    } else {
        int mid = start + (end - start) / 2;
        int left_index = build(start, mid, problems, range_tree);
        int right_index = build(mid + 1, end, problems, range_tree);
        range_tree[current_index].left = left_index;
        range_tree[current_index].right = right_index;
        range_tree[current_index].max = max(range_tree[left_index].max, range_tree[right_index].max);
        range_tree[current_index].sum = range_tree[left_index].sum + range_tree[right_index].sum;
        range_tree[current_index].first_val = range_tree[left_index].first_val;
        range_tree[current_index].last_val = range_tree[right_index].last_val;


        range_tree[current_index].is_dec = (
            range_tree[left_index].is_dec
            && range_tree[right_index].is_dec
            && range_tree[left_index].last_val >= range_tree[right_index].first_val
        );
           
        range_tree[current_index].is_inc = (
            range_tree[left_index].is_inc
            && range_tree[right_index].is_inc
            && range_tree[left_index].last_val <= range_tree[right_index].first_val
        );

        return current_index;
    }
}


void update(int x, int new_value, int root_index, vector<Node>& range_tree) {
    if (range_tree[root_index].range_start == range_tree[root_index].range_end) {
        range_tree[root_index].max = new_value;
        range_tree[root_index].sum = new_value;
        range_tree[root_index].first_val = new_value;
        range_tree[root_index].last_val = new_value;
    } else {
        int left_index = range_tree[root_index].left;
        int right_index = range_tree[root_index].right;
        if (range_tree[left_index].range_start <= x && x <= range_tree[left_index].range_end) {
            update(x, new_value, left_index, range_tree);
        } else if (range_tree[right_index].range_start <= x && x <= range_tree[right_index].range_end) {
            update(x, new_value, right_index, range_tree);
        }
        range_tree[root_index].max = max(range_tree[left_index].max, range_tree[right_index].max);
        range_tree[root_index].sum = range_tree[left_index].sum + range_tree[right_index].sum;
        range_tree[root_index].is_dec = (
            range_tree[left_index].is_dec
            && range_tree[right_index].is_dec
            && range_tree[left_index].last_val >= range_tree[right_index].first_val
        );
        range_tree[root_index].is_inc = (
            range_tree[left_index].is_inc
            && range_tree[right_index].is_inc
            && range_tree[left_index].last_val <= range_tree[right_index].first_val
        );
        range_tree[root_index].first_val = range_tree[left_index].first_val;
        range_tree[root_index].last_val = range_tree[right_index].last_val;
    }
}


QueryResult search(int start, int end, int root_index, vector<Node>& range_tree) {
    if (range_tree[root_index].range_start == start && range_tree[root_index].range_end == end) {
        return {
            range_tree[root_index].max,
            range_tree[root_index].sum,
            range_tree[root_index].is_inc,
            range_tree[root_index].is_dec,
            range_tree[root_index].first_val,
            range_tree[root_index].last_val,
        };
    } else {
        int left_index = range_tree[root_index].left;
        int left_range_end = range_tree[left_index].range_end;
        int right_index = range_tree[root_index].right;

        if (start <= left_range_end && end <= left_range_end) {
            return search(start, end, left_index, range_tree);
        } else if (start > left_range_end && end > left_range_end) {
            return search(start, end, right_index, range_tree);
        } else {
            QueryResult left_search = search(start, left_range_end, left_index, range_tree);
            QueryResult right_search = search(left_range_end + 1, end, right_index, range_tree);
            return {
                max(left_search.max, right_search.max),
                left_search.sum + right_search.sum,
                (
                    left_search.is_inc
                    && right_search.is_inc
                    && left_search.last_val <= right_search.first_val
                ),
                (
                    left_search.is_dec
                    && right_search.is_dec
                    && left_search.last_val >= right_search.first_val
                ),
                left_search.first_val,
                right_search.last_val,
            };
        } 
    }
}
