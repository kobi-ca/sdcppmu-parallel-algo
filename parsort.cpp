//
// Created by kobi on 7/25/20.
//

#include <algorithm>
#include <execution>
#include <string>
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

    std::clog << "Elements: " << numElems << '\n';

    std::vector<std::string> coll;
    for (int i = 0; i < numElems / 2; i++) {
        (void) coll.emplace_back("id" + std::to_string(i));
        (void) coll.emplace_back("ID" + std::to_string(i));
    }

    // loop to make measurements mature:
    for (int i{0}; i < 5; ++i) {
        Timer t;
        sort(begin(coll), end(coll));
        t.printDiff("sequential:\t\t");

        sort(std::execution::par, begin(coll), end(coll));
        t.printDiff("parallel:\t\t");

        sort(std::execution::par_unseq, begin(coll), end(coll));
        t.printDiff("parallel unseq:\t\t");

        std::clog << '\n';
    }

    std::clog << "with lambda\n";
    for (int i{0}; i < 5; ++i) {
        Timer t;
        const auto l([](const auto &v1, const auto &v2) { return v1.substr(2) < v2.substr(2); });
        sort(begin(coll), end(coll), l);
        t.printDiff("sequential: ");

        sort(std::execution::par, begin(coll), end(coll), l);
        t.printDiff("parallel:   ");

        std::clog << '\n';
    }

    std::clog << "improved lambda\n";
    for (int i{0}; i < 5; ++i) {
        Timer t;
        const auto l([](const auto &v1, const auto &v2) { return std::string_view(v1).substr(2) < std::string_view(v2).substr(2); });
        sort(begin(coll), end(coll), l);
        t.printDiff("sequential: ");

        sort(std::execution::par, begin(coll), end(coll), l);
        t.printDiff("parallel:   ");

        std::clog << '\n';
    }
}
