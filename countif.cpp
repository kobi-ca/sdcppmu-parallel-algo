//
// Created by kobi on 7/25/20.
//

#include <cstdlib>  // for atoi()
#include <execution>// for the execution policy
#include <iostream>
#include <numeric>
#include <vector>

#include "timer.hpp"

template <typename CONT>
void test (const CONT& c) {
    // loop to make measurements mature:
    for (int i{0}; i < 5; ++i) {
        Timer t;
        // sequential execution:
        auto num = std::count_if(std::execution::seq,
                                 c.begin(), c.end(),
                                 [](const auto val) {
                                     return val.val % 2 == 0;
                                 });
        t.printDiff("sequential: ");
        std::clog << "result " << num << '\n';

        // parallel execution:
        num = std::count_if(std::execution::par,
                            c.begin(), c.end(),
                            [](const auto val) {
                                return val.val % 2 == 0;
                            });
        t.printDiff("parallel:   ");
        std::clog << "result " << num << '\n';
        std::cout << '\n';
    }
};

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

    std::clog << "Elements: " << numElems << '\n';

    // initialize numElems values without square root:
    struct AlignedInt final {
        explicit AlignedInt(uint64_t v) : val{v}{}
        alignas(std::max_align_t)  uint64_t val;
    };
    struct NonAlignedInt final {
        explicit  NonAlignedInt(uint64_t v) : val{v}{}
        uint64_t val;
    };
    std::vector<AlignedInt> coll_aligned;
    std::vector<NonAlignedInt> coll;
    coll.reserve(numElems);
    for (uint64_t i = 0; i < numElems; ++i) {
        coll.emplace_back(NonAlignedInt{i});
        coll_aligned.emplace_back(AlignedInt{i});
    }

    std::clog << "Non aligned\n";
    test(coll);
    std::clog << "aligned\n";
    test(coll_aligned);
}
