#include <cmath>    // for sqrt()
#include <execution>// for the execution policy
#include <numeric>
#include <vector>

int main() {
    constexpr auto numElems = 1000U;

    struct Data final {
        double value{};// initial value
        double sqrt{}; // parallel computed square root
    };

    // initialize numElems values without square root:
    std::vector<Data> coll;
    coll.reserve(numElems);
    for (auto i = 0; i < numElems; ++i) {
        coll.push_back(Data{i * 4.37, 0});
    }

    // parallel computation of square roots:
    for_each(std::execution::par,
             coll.begin(), coll.end(),
             [](auto &val) {
                 val.sqrt = std::sqrt(val.value);
             });
}
