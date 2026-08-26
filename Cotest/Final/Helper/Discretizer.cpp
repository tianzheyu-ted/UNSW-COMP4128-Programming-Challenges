#include <vector>
#include <algorithm>

using namespace std;

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