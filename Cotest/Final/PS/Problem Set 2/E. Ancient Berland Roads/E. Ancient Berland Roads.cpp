
#include <set>
#include <vector>
#include <iostream>


using namespace std;

struct City {
    int id;
    int population;
    set<int> neighbors;
};

struct Road {
    int id;
    int city1;
    int city2;
};

struct Query {
    char type;
    int x;
    int y;
};

long long dfsRec(City& src, vector<City>& cities, vector<int>& visited, int mark);
void initDSU(int n, vector<City>& cities, vector<int>& parents, vector<long long>& pop_sum, multiset<long long>& max_pops);
int find(int x, vector<int>& parents);
void unite(int x, int y, vector<int>& parents, vector<long long>& pop_sum, multiset<long long>& max_pops);
long long dfsRec(City& src, vector<City>& cities, vector<int>& visited, int mark);



int main() {
    int n, m, q;
    cin >> n;
    cin >> m;
    cin >> q;

    vector<City> cities(n, {0, 0});
    for (int i = 0; i < n; i++) {
        cities[i].id = i + 1;
        cin >> cities[i].population;
    }

    vector<Road> roads(m, {0, 0, 0});
    for (int i = 0; i < m; i++) {
        roads[i].id = i + 1;
        cin >> roads[i].city1;
        cin >> roads[i].city2;

        int u = roads[i].city1 - 1;
        int v = roads[i].city2 - 1;

        cities[u].neighbors.insert(roads[i].city2);
        cities[v].neighbors.insert(roads[i].city1);
    }

    vector<Query> queries(q, {'A', -1, -1});
    vector<bool> road_deleted(m, false);
    for (int i = 0; i < q; i++) {
        char cmd;
        cin >> cmd;

        if (cmd == 'D') {
            int road_id;
            cin >> road_id;
            queries[i] = {'D', road_id - 1, -1};
            road_deleted[road_id - 1] = true;
            // Road road = roads[road_id - 1];
            // cities[road.city1 - 1].neighbors.erase(road.city2);
            // cities[road.city2 - 1].neighbors.erase(road.city1);
        } else if (cmd == 'P') {
            int city_id;
            cin >> city_id;
            int population;
            cin >> population;
            queries[i] = {'P', city_id - 1, population};
            swap(cities[city_id - 1].population, queries[i].y);
            // cities[city_id - 1].population = population;
        }

        // vector<int> visited(n, -1);
        // long long max_population = 0;
        // for (int i = 0; i < n; i++) {
        //     if (visited[i] == -1) {
        //         max_population = max(dfsRec(cities[i], cities, visited, i), max_population);
        //     }
        // }

        // cout << max_population << '\n';
    }


    vector<int> parents;
    vector<long long> pop_sum;
    multiset<long long> max_pops;

    initDSU(n, cities, parents, pop_sum, max_pops);

    for (int i = 0; i < m; i++) {
        if (!road_deleted[i]) {
            unite(roads[i].city1 - 1, roads[i].city2 - 1, parents, pop_sum, max_pops);
        }
    }


    vector<long long> result(q);

    for (int i = q - 1; i >= 0; i--) {
        result[i] = *max_pops.rbegin(); 

        if (queries[i].type == 'D') {
            int road_idx = queries[i].x;
            unite(roads[road_idx].city1 - 1, roads[road_idx].city2 - 1, parents, pop_sum, max_pops);
        } else if (queries[i].type == 'P') {
            int city_idx = queries[i].x;
            int old_population = queries[i].y;

            int root = find(city_idx, parents);
            max_pops.erase(max_pops.find(pop_sum[root]));
            pop_sum[root] += (old_population - cities[city_idx].population);
            cities[city_idx].population = old_population;
            max_pops.insert(pop_sum[root]);
        }
    }

    for (int i = 0; i < q; i++) {
        cout << result[i] << "\n";
    }
}


void initDSU(int n, vector<City>& cities, vector<int>& parents, vector<long long>& pop_sum, multiset<long long>& max_pops) {
    parents.resize(n); 
    pop_sum.resize(n);
    for (int i = 0; i < n; i++) {
        parents[i] = i;
        pop_sum[i] = cities[i].population;
        max_pops.insert(pop_sum[i]);
    }
}


int find(int x, vector<int>& parents) {
    if (parents[x] == x) {
        return x;
    } else {
        parents[x] = find(parents[x], parents);
        return parents[x];
    }
}


void unite(int x, int y, vector<int>& parents, vector<long long>& pop_sum, multiset<long long>& max_pops) {
    int rootX = find(x, parents);
    int rootY = find(y, parents);
    if (rootX != rootY) {
        max_pops.erase(max_pops.find(pop_sum[rootX]));
        max_pops.erase(max_pops.find(pop_sum[rootY]));

        parents[rootX] = rootY;
        pop_sum[rootY] += pop_sum[rootX];

        max_pops.insert(pop_sum[rootY]);
    }
}


long long dfsRec(City& src, vector<City>& cities, vector<int>& visited, int mark) {
    if (visited[src.id - 1] != -1) {
        return 0;
    } else {
        visited[src.id - 1] = mark;
        long long result = src.population;
        for (int i : src.neighbors) {
            result += dfsRec(cities[i - 1], cities, visited, mark);
        }
        return result;
    }
}