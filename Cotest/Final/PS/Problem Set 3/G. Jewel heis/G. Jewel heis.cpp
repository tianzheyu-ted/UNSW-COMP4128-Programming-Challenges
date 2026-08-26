
#include <map>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Node {
    int value;
    int left;
    int right;
    pair<int, int> range;
};

struct Jewel {
    int x;
    int y;
    int color;
};

struct Region {
    int left;
    int right;
    int height;
    int area;
    int excluded_color;
};

int build(vector<Node>& tree, pair<int, int> range);
void update(int root, vector<Node>& tree, int index, int value);
int search(int root, vector<Node>& tree, pair<int, int> range);

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;

        vector<int> x_all;
        x_all.reserve(n);

        vector<Jewel> jewels;
        jewels.reserve(n);

        vector<vector<Jewel>> jewels_color(k + 1, vector<Jewel>());
        for (int j = 0; j < n; j++) {
            int x, y, color;
            cin >> x >> y >> color;
            x_all.push_back(x);
            jewels.push_back({x, y, color});
            jewels_color[color].push_back({x, y, color});
        }

        x_all.push_back(0); 
        x_all.push_back(1000000001); 

        sort(x_all.begin(), x_all.end(), [] (auto& a, auto& b) {
            return a < b;
        });

        x_all.erase(unique(x_all.begin(), x_all.end()), x_all.end());

        unordered_map<int, int> x_to_range_index;
        for (int j = 0; j < x_all.size(); j++) {
            x_to_range_index[x_all[j]] = j + 1;
        }

        vector<Region> regions;
        regions.reserve(3 * n);
        for (int m = 1; m < k + 1; m++) {
            map<int, int> x_map;
            for (int j = 0; j < jewels_color[m].size(); j++) {
                if (jewels_color[m][j].color != m) continue;
                if (x_map.count(jewels_color[m][j].x)) {
                    x_map[jewels_color[m][j].x] = min(x_map[jewels_color[m][j].x], jewels_color[m][j].y);
                } else {
                    x_map[jewels_color[m][j].x] = jewels_color[m][j].y;
                }
            }

            vector<pair<int, int>> x(x_map.size() + 2);
            x[0] = {0, 0};
            x.back() = {1000000001, 0};

            int index = 1;
            auto it = x_map.begin();
            while (it != x_map.end()) {
                x[index] = *it;
                index++;
                it = next(it);
            }
            
            deque<int> dq;
            dq.push_back(x[0].first);
            for (int j = 1; j < x.size(); j++) {
                Region inf_region;
                inf_region.height = 2000000000;
                inf_region.left = x[j-1].first;
                inf_region.right = x[j].first;
                regions.push_back(inf_region);

                while (!dq.empty() && x[j].second < x[dq.back()].second) {
                    int current_index = dq.back();
                    dq.pop_back();
                    int height = x[current_index].second;
                    int width = j - dq.back() - 1;
                    
                    Region region;
                    region.area = height * width;
                    region.height = height - 1;
                    region.left = x[dq.back()].first;
                    region.right = x[j].first;
                    regions.push_back(region);
                }
                dq.push_back(j);
            }
        }

        sort(jewels.begin(), jewels.end(), [] (auto& a, auto& b) {
            return a.y < b.y;
        });
    
        sort(regions.begin(), regions.end(), [] (auto& a, auto& b) {
            if (a.height == b.height) {
                if (a.left == b.left) {
                    return a.right < b.right;
                }
                return a.left < b.left;
            }
            return a.height < b.height;
        });

        vector<Node> tree;
        tree.reserve(4 * n);
        int root = build(tree, {1, x_all.size() + 1});

        int max_stolen = 0;
        int jewel_pointer = 0;

        for (int j = 0; j < regions.size(); j++) {
            int height = regions[j].height;
            while (jewel_pointer < jewels.size() && jewels[jewel_pointer].y <= height) {
                int index = x_to_range_index[jewels[jewel_pointer].x];
                update(root, tree, index, 1);
                jewel_pointer++;
            }
            int left = x_to_range_index[regions[j].left] + 1;
            int right = x_to_range_index[regions[j].right] - 1;
            if (left <= right) {
                max_stolen = max(max_stolen, search(root, tree, {left, right}));
            }
        }

        cout << max_stolen << '\n';
    }
}


int build(vector<Node>& tree, pair<int, int> range) {
    int i = tree.size();
    tree.push_back({0, -1, -1, range});
    if (range.first == range.second) {
        return i;
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        int left = build(tree, {range.first, mid});
        int right = build(tree, {mid + 1, range.second});
        tree[i].left = left;
        tree[i].right = right;
        return i;
    }
}


void update(int root, vector<Node>& tree, int index, int value) {
    if (tree[root].range.first == tree[root].range.second) {
        tree[root].value += value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (tree[left].range.first <= index && index <= tree[left].range.second) {
            update(left, tree, index, value);
        } else {
            update(right, tree, index, value);
        }
        tree[root].value = tree[left].value + tree[right].value;
    }
}


int search(int root, vector<Node>& tree, pair<int, int> range) {
    if (tree[root].range == range) {
        return tree[root].value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (range.second <= tree[left].range.second) {
            return search(left, tree, range);
        } else if (range.first >= tree[right].range.first) {
            return search(right, tree, range);
        } else {
            return (
                search(left, tree, {range.first, tree[left].range.second})
                + search(right, tree, {tree[right].range.first, range.second})
            );
        }   
    }
}