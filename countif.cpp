//
// Created by kobi on 7/25/20.
//

#include <cstdlib>  // for atoi()
#include <execution>// for the execution policy
#include <iostream>
#include <numeric>
#include <vector>

#include "timer.hpp"

int main(int argc, char *argv[]) {
    // initialize numElems from command line (default: 1000)
    auto numElems = 1000ULL;
    if (argc > 1) {
        char *p_end;
        numElems = std::strtol(argv[1], &p_end, 10);
        if (p_end == argv[1]) {
            return -1;
        }
    }

    // initialize numElems values without square root:
    std::vector<uint64_t> coll;
    coll.reserve(numElems);
    for (int i = 0; i < numElems; ++i) {
        coll.push_back(i);
    }

    // loop to make measurements mature:
    for (int i{0}; i < 5; ++i) {
        Timer t;
        // sequential execution:
        auto num = std::count_if(std::execution::seq,
                                 coll.begin(), coll.end(),
                                 [](const auto val) {
                                     return val % 2 == 0;
                                 });
        t.printDiff("sequential: ");
        std::clog << "result " << num << '\n';

        // parallel execution:
        num = std::count_if(std::execution::par,
                            coll.begin(), coll.end(),
                            [](const auto val) {
                                return val % 2 == 0;
                            });
        t.printDiff("parallel:   ");
        std::clog << "result " << num << '\n';
        std::cout << '\n';
    }
}
