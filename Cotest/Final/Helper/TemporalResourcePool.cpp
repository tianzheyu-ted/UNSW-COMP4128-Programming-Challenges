#include <set>
#include <queue>
#include <iostream>
#include <functional>
#include <optional>

using namespace std;

/**
 * 泛型调度器 TemporalResourcePool 使用指南
    TemporalResourcePool 是一个高度抽象的时间状态机模型。
    它将资源在“可用（活跃池）”和“不可用（冷却池）”之间的流转逻辑封装起来，调用方只需要注入具体的业务规则。
    使用该类解决带有时间冷却/状态流转的分配问题，只需遵循以下四个步骤：

    第一步：定义资源结构体 (定义泛型 T)
    将参与业务逻辑的所有属性（特别是用于比较和记录时间的属性）打包成一个结构体。

    第二步：定义三大全局规则并实例化
    使用 Lambda 表达式定义资源的排序和时间提取规则，并在实例化时注入。
        1.  活跃池规则 (active_cmp)：定义可用资源在集合中的排序方式。
            例如：按价格升序排列，方便二分查找
        2.  冷却池规则 (cooldown_cmp)：定义资源在优先队列中的出炉顺序。
            注意：priority_queue 默认大顶堆，若需最早完工的先出炉（小顶堆），需使用 >
        3.  时间提取规则 (extractor)：告诉类哪个字段代表“解除冷却的时间”

    第三步：初始化资源
    在模拟开始前，将所有初始状态的资源加入调度器。

    第四步：在时间线上推动状态，并消费资源
    当业务事件触发时（如顾客到达、任务下发），执行时间推进和资源匹配逻辑。
 */



// T: 资源类型, TimeType: 时间维度类型
template <typename T, typename TimeType>
class TemporalResourcePool {
public:
    // 定义外部传入的规则签名
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

    // 初始化时注入资源
    void addResource(const T& resource) {
        active_pool.insert(resource);
    }

    // 核心流转机制：根据当前时间，将冷却完毕的资源放回活跃池
    void advanceTime(TimeType current_time) {
        while (!cooldown_queue.empty() && get_ready_time(cooldown_queue.top()) <= current_time) {
            active_pool.insert(cooldown_queue.top());
            cooldown_queue.pop();
        }
    }

    // 核心匹配机制：传入一个查找逻辑，返回匹配的资源并执行下架逻辑
    template <typename FindFunc, typename UpdateFunc>
    std::optional<T> consumeBest(FindFunc find_logic, UpdateFunc update_cooldown_logic) {
        // 直接调用传入的逻辑
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


struct Item {
    int id;               // 资源唯一标识
    long long price;      // 业务属性（例如：价格）
    long long craft_time; // 业务属性（例如：冷却周期）
    long long ready_time; // 关键状态属性：何时能解除冷却重新进入活跃池
};


int main() {
    // 1. 活跃池规则 (active_cmp)：定义可用资源在集合中的排序方式。
    // 例如：按价格升序排列，方便二分查找
    auto active_cmp = [](const Item& a, const Item& b) {
        return a.price < b.price; 
    };

    // 2. 冷却池规则 (cooldown_cmp)：定义资源在优先队列中的出炉顺序。
    // 注意：priority_queue 默认大顶堆，若需最早完工的先出炉（小顶堆），需使用 >
    auto cooldown_cmp = [](const Item& a, const Item& b) {
        return a.ready_time > b.ready_time; 
    };

    // 3. 时间提取规则 (extractor)：告诉类哪个字段代表“解除冷却的时间”
    auto extractor = [](const Item& a) {
        return a.ready_time; 
    };

    // 实例化调度器
    TemporalResourcePool<Item, long long> shop(active_cmp, cooldown_cmp, extractor);

    int n;

    // 假设 n 个资源初始均为可用状态 (ready_time = 0)
    for (int i = 0; i < n; i++) {
        long long price, craft_time;
        cin >> price >> craft_time;
        shop.addResource({i + 1, price, craft_time, 0});
    }

    long long current_time = 10; // 当前事件的时间戳
    long long budget = 500;      // 业务条件

    // 1. 推进时间：自动将所有冷却完毕的资源从冷却池移回活跃池
    shop.advanceTime(current_time);

    // 2. 注入【寻找逻辑】：在当前的活跃池中如何寻找最优资源
    auto find_logic = [budget](const auto& pool) {
        Item dummy = {-1, budget, -1, -1}; 
        auto it = pool.upper_bound(dummy); // 寻找第一个大于 budget 的资源
        if (it == pool.begin()) return pool.end(); // 若没有符合条件的，返回 end()
        return std::prev(it); // 退一步获取 <= budget 的最大资源
    };

    // 3. 注入【更新逻辑】：资源被消费后，其状态属性应如何改变
    auto update_logic = [current_time](Item& item) {
        item.ready_time = current_time + item.craft_time; // 重新计算冷却完成时间
    };

    // 4. 执行消费：调度器会自动完成资源的下架、状态更新以及进入冷却池的操作
    auto result = shop.consumeBest(find_logic, update_logic);

    // 处理返回结果 (std::optional)
    if (result.has_value()) {
        cout << "成功分配资源 ID: " << result->id << "\n";
    } else {
        cout << "无可用资源匹配\n";
    }
}