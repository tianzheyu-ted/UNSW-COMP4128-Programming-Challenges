#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;


template <typename T, typename Merge = std::plus<T>>
class RangeTree {
public:
    RangeTree(int start, int end, T id, Merge op = Merge()) 
        : identity(id), merge_op(op) {
        int n = end - start + 1;
        tree.reserve(4 * n);
        tree_root = build(start, end);
    }

    void update(int idx, T val) {
        update_rec(idx, val, tree_root);
    }

    T query(int L, int R) {
        if (L > R) return identity;
        return query_rec(L, R, tree_root);
    }

private:
    struct Node {
        pair<int, int> range;
        T val;
        int left;
        int right;
    };

    int tree_root;
    vector<Node> tree;
    T identity;
    Merge merge_op;

    int build(int start, int end) {
        int index = tree.size();
        tree.push_back({{start, end}, identity, -1, -1});
        if (start == end) {
            return index;
        } else {
            int mid = start + (end - start) / 2;
            int left_child = build(start, mid);
            int right_child = build(mid + 1, end);
            tree[index].left = left_child;
            tree[index].right = right_child;
            tree[index].val = merge_op(tree[left_child].val, tree[right_child].val);
            return index;
        }
    }

    void update_rec(int idx, T val, int root) {
        if (tree[root].range.first == tree[root].range.second) {
            tree[root].val = val;
        } else {
            int left_child = tree[root].left;
            int right_child = tree[root].right;
            int mid = tree[root].range.first + (tree[root].range.second - tree[root].range.first) / 2;
            
            if (idx <= mid) {
                update_rec(idx, val, left_child);
            } else {
                update_rec(idx, val, right_child);
            }
            tree[root].val = merge_op(tree[left_child].val, tree[right_child].val);
        }
    }

    T query_rec(int L, int R, int root) {
        if (R < tree[root].range.first || L > tree[root].range.second) {
            return identity;
        }
        if (L <= tree[root].range.first && tree[root].range.second <= R) {
            return tree[root].val;
        }
        int left_child = tree[root].left;
        int right_child = tree[root].right;
        return merge_op(
            query_rec(L, R, left_child),
            query_rec(L, R, right_child)
        );
    }
};

int main() {
    // 定义合并逻辑：取两者的最大值
    auto max_op = [](int a, int b) { return max(a, b); };

    // 初始化：区间 [0, 100]，单位元为极小值 -1e9，合并逻辑为 max_op
    RangeTree<int, decltype(max_op)> rt(0, 100, -1e9, max_op);

    rt.update(5, 50);
    rt.update(10, 100);
    cout << rt.query(0, 20) << "\n"; // 自动返回 100    
}