
#include <execution>
#include <iostream>
#include <numeric>// for reduce()
#include <vector>

void printSum(const long num) {
    // create coll with num sequences of 1 2 3 4:
    std::vector<long> coll;
    coll.reserve(num * 4);
    for (long i = 0; i < num; ++i) {
        coll.insert(coll.end(), {1, 2, 3, 4});
    }

    const auto squaredSum = [](auto sum, auto val) {
        return sum + val * val;
    };

    const auto sum = std::reduce(std::execution::par,
                                 coll.begin(), coll.end(),
                                 0L,
                                 squaredSum);
    std::clog << "reduce():     " << sum << '\n';
}

int main() {
    printSum(1);
    printSum(1000);
    printSum(1000000);
    printSum(10000000);
}
