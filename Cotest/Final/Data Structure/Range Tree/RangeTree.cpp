
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

        void update(int start, int end) {
            update_rec(start, end, tree_root);
        }

        int search(int start, int end) {
            return search_rec(start, end, tree_root);
        }

    private:
        struct Node {
            pair<int, int> range;
            int value;
            int left;
            int right;
        };

        int n;
        int tree_root;
        vector<Node> tree;

        int build(int start, int end) {
            int index = tree.size();
            tree.push_back({{start, end}, 0, -1, -1});
            if (start == end) {
                return index;
            } else {
                int mid = start + (end - start) / 2;
                int left = build(start, mid);
                int right = build(mid + 1, end);
                tree[index].value = tree[left].value + tree[right].value;
                tree[index].left = left;
                tree[index].right = right;
                return index;
            }
        }

        void update_rec(int start, int end, int root) {
            if (tree[root].range.first == tree[root].range.second) {
                tree[root].value += 1;
            } else {
                int left = tree[root].left;
                int right = tree[root].right;
                if (end <= tree[left].range.second) {
                    update_rec(start, end, left);
                } else if (tree[right].range.first <= start) {
                    update_rec(start, end, right);
                } else {
                    update_rec(start, tree[left].range.second, left);
                    update_rec(tree[right].range.first, end, right);
                }
                tree[root].value = tree[left].value + tree[right].value;
            }
        }

        int search_rec(int start, int end, int root) {
        if (start == tree[root].range.first && end == tree[root].range.second) {
            return tree[root].value;
        } else {
            int left = tree[root].left;
            int right = tree[root].right;
            if (end <= tree[left].range.second) {
                return search_rec(start, end, left);
            } else if (tree[right].range.first <= start) {
                return search_rec(start, end, right);    
            } else {
                return (
                    search_rec(start, tree[left].range.second, left)
                    + search_rec(tree[right].range.first, end, right)
                );
            }
        }
    }
};