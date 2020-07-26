
#include <iostream>
#include <numeric>// for accumulate()
#include <vector>

void printSum(const long num) {
    // create coll with num sequences of 1 2 3 4:
    std::vector<long> coll;
    coll.reserve(num * 4);
    for (long i = 0; i < num; ++i) {
        coll.insert(coll.end(), {1, 2, 3, 4});
    }

    const auto squaredSum = [](const auto sum, const auto val) {
        return sum + val * val;
    };

    const auto sum = std::accumulate(coll.begin(), coll.end(),
                                     0L,
                                     squaredSum);
    std::clog << "accumulate(): " << sum << '\n';
}

int main() {
    printSum(1);
    printSum(1000);
    printSum(1000000);
    printSum(10000000);
}
