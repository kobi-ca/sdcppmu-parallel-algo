//
// Created by kobi on 7/25/20.
//

//
// Created by kobi on 7/25/20.
//

#include <cstdlib>  // for atoi()
#include <execution>// for the execution policy
#include <iostream>
#include <numeric>
#include <vector>

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
    std::vector<uint64_t> coll;
    coll.reserve(numElems);
    for (int i = 0; i < numElems; ++i) {
        coll.push_back(i);
    }

    try {
        std::size_t num{};
        if (std::getenv("REGULAR")) {
            num = std::count_if(
                    coll.begin(), coll.end(),
                    [](const auto val) {
                        if (val == 100) throw std::logic_error("regular");
                        return val % 2 == 0;
                    });
            std::clog << "result " << num << '\n';
        }

        // sequential execution:
        num = std::count_if(std::execution::seq,
                            coll.begin(), coll.end(),
                            [](const auto val) {
                                if (val == 100) throw std::logic_error("seq");
                                return val % 2 == 0;
                            });
        std::clog << "result " << num << '\n';
    } catch (const std::exception &ex) {
        std::clog << ex.what() << '\n';
    }

    std::cout << '\n';
}
