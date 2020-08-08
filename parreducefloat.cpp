
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

void printSum(const long num) {
    // create coll with num sequences of 0.1 0.3 0.0001:
    std::vector<double> coll;
    coll.reserve(num * 4);
    for (long i = 0; i < num; ++i) {
        coll.insert(coll.end(), {0.1, 0.3, 0.00001});
    }

    const auto sum1 = std::accumulate(coll.begin(), coll.end(),
                                      0.0);
    std::clog << "accumulate(): " << sum1 << '\n';
    const auto sum2 = std::reduce(std::execution::par,
                                  coll.begin(), coll.end(),
                                  0.0);
    std::clog << "reduce():     " << sum2 << '\n';
    std::clog << (sum1 == sum2 ? "equal\n" : "differ\n");
}

#include <iomanip>

int main() {
    if (::getenv("PREC")) {
        std::clog << std::setprecision(20);
    }
    printSum(1);
    printSum(1000);
    printSum(1000000);
    printSum(10000000);
}
