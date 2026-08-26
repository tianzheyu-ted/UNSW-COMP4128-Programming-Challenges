
#include <map>
#include <set>
#include <queue>
#include <functional>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Item {
    int id;
    long long price;
    long long craft_time;
    long long ready_time;
};

template <typename T, typename TimeType>
class TemporalResourcePool {
public:
    using ActiveCompare = std::function<bool(const T&, const T&)>;
    using CooldownCompare = std::function<bool(const T&, const T&)>;
    using TimeExtractor = std::function<TimeType(const T&)>;
private:
    std::set<T, ActiveCompare> active_pool;
    std::priority_queue<T, std::vector<T>, CooldownCompare> cooldown_queue;
    TimeExtractor get_ready_time;
public:
    TemporalResourcePool(ActiveCompare active_cmp, CooldownCompare cd_cmp, TimeExtractor extractor)
        : active_pool(active_cmp), cooldown_queue(cd_cmp), get_ready_time(extractor) {}
    void addResource(const T& resource) {
        active_pool.insert(resource);
    }
    void advanceTime(TimeType current_time) {
        while (!cooldown_queue.empty() && get_ready_time(cooldown_queue.top()) <= current_time) {
            active_pool.insert(cooldown_queue.top());
            cooldown_queue.pop();
        }
    }
    template <typename FindFunc, typename UpdateFunc>
    std::optional<T> consumeBest(FindFunc find_logic, UpdateFunc update_cooldown_logic) {
        auto it = find_logic(active_pool);
        if (it == active_pool.end()) {
            return std::nullopt; 
        }
        T best_resource = *it;
        active_pool.erase(it); 
        update_cooldown_logic(best_resource); 
        cooldown_queue.push(best_resource);
        return best_resource;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    auto active_cmp = [](const Item& a, const Item& b) {
        return a.price < b.price; 
    };

    auto cooldown_cmp = [](const Item& a, const Item& b) {
        return a.ready_time > b.ready_time; 
    };

    auto extractor = [](const Item& a) {
        return a.ready_time; 
    };

    TemporalResourcePool<Item, long long> shop(active_cmp, cooldown_cmp, extractor);

    for (int i = 0; i < n; i++) {
        long long price, craft_time;
        cin >> price >> craft_time;
        shop.addResource({i + 1, price, craft_time, 0});
    }

    for (int i = 0; i < m; i++) {
        long long visit_date, budget;
        cin >> visit_date >> budget;
        shop.advanceTime(visit_date);
        auto find_logic = [budget](const auto& pool) {
            Item dummy = {-1, budget, -1, -1};
            auto it = pool.upper_bound(dummy);
            if (it == pool.begin()) return pool.end();
            return std::prev(it);
        };

        auto update_logic = [visit_date](Item& item) {
            item.ready_time = visit_date + item.craft_time;
        };

        auto result = shop.consumeBest(find_logic, update_logic);
        if (result.has_value()) {
            cout << result->id << " ";
        } else {
            cout << 0 << " ";
        }
    }

    cout << '\n';
}