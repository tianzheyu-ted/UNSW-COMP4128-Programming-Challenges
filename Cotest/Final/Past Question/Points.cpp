
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct RangeTree {
public:
    RangeTree(int start, int end) {
        n = end - start + 1;
        tree.reserve(4 * n);
        tree_root = build(start, end);
    }

    void update(int pos, int new_max_y) {
        update_rec(pos, new_max_y, tree_root);
    }

    int search(int query_start, int target_y) {
        return search_rec(query_start, target_y, tree_root);
    }

private:
    struct Node {
        pair<int, int> range;
        int max_y;
        int left;
        int right;
    };

    int n;
    int tree_root;
    vector<Node> tree;

    int build(int start, int end) {
        int index = tree.size();
        tree.push_back({{start, end}, -1, -1, -1});
        if (start == end) {
            return index;
        } else {
            int mid = start + (end - start) / 2;
            int left = build(start, mid);
            int right = build(mid + 1, end);
            tree[index].max_y = max(tree[left].max_y, tree[right].max_y);
            tree[index].left = left;
            tree[index].right = right;
            return index;
        }
    }

    void update_rec(int pos, int new_max_y, int root) {
        if (tree[root].range.first == tree[root].range.second) {
            tree[root].max_y = new_max_y;
        } else {
            int left = tree[root].left;
            int right = tree[root].right;
            int mid = tree[root].range.first + (tree[root].range.second - tree[root].range.first) / 2;
            
            if (pos <= mid) {
                update_rec(pos, new_max_y, left);
            } else {
                update_rec(pos, new_max_y, right);
            }
            tree[root].max_y = max(tree[left].max_y, tree[right].max_y);
        }
    }

    int search_rec(int query_start, int target_y, int root) {
        if (tree[root].range.second < query_start || tree[root].max_y <= target_y) {
            return -1;
        }
        
        if (tree[root].range.first == tree[root].range.second) {
            return tree[root].range.first;
        }
        
        int left = tree[root].left;
        int right = tree[root].right;
        
        int res = search_rec(query_start, target_y, left);
        if (res == -1) {
            res = search_rec(query_start, target_y, right);
        }
        return res;
    }
};

template <typename T>
class Discretizer {
    private:
        vector<T> values;
        bool built = false;

    public:
        void add(T val) {
            values.push_back(val);
            built = false;
        }

        void build() {
            sort(values.begin(), values.end());
            values.erase(unique(values.begin(), values.end()), values.end());
            built = true;
        }

        int get_id(T val) const {
            return lower_bound(values.begin(), values.end(), val) - values.begin();
        }

        T get_val(int id) const {
            return values[id];
        }

        int size() const {
            return values.size();
        }
};

int main() {
    int n;
    cin >> n;

    vector<pair<string, pair<int, int>>> requests(n);
    Discretizer<int> dx;

    for (int i = 0; i < n; i++) {
        cin >> requests[i].first >> requests[i].second.first >> requests[i].second.second;
        dx.add(requests[i].second.first);
    }

    dx.build();
    RangeTree rt(0, dx.size() - 1);
    vector<set<int>> y_sets(dx.size());

    for (auto& req : requests) {
        string type = req.first;
        int original_x = req.second.first;
        int y = req.second.second;

        int mapped_x = dx.get_id(original_x); 
        
        if (type == "add") {
            y_sets[mapped_x].insert(y);
            int max_y = *y_sets[mapped_x].rbegin();
            rt.update(mapped_x, max_y);
        } else if (type == "find") {
            int query_start = mapped_x + 1;
            if (query_start >= dx.size()) {
                cout << -1 << "\n";
            } else {
                int found_x_id = rt.search(query_start, y);
                if (found_x_id == -1) {
                    cout << -1 << "\n";
                } else {
                    int ans_x = dx.get_val(found_x_id);
                    int ans_y = *y_sets[found_x_id].upper_bound(y);
                    cout << ans_x << " " << ans_y << "\n";
                }
            }
        } else if (type == "remove") {
            y_sets[mapped_x].erase(y);
            int max_y = y_sets[mapped_x].empty() ? -1 : *y_sets[mapped_x].rbegin();
            rt.update(mapped_x, max_y);
        }
    }
}