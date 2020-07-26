
#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <string>


/********************************************
 * timer to print elapsed time
 ********************************************/

class Timer final {
private:
    std::chrono::steady_clock::time_point last;

public:
    explicit Timer()
        : last{std::chrono::steady_clock::now()} {
    }
    void printDiff(const std::string &msg = "Timer diff: ") {
        auto now{std::chrono::steady_clock::now()};
        std::chrono::duration<double, std::milli> diff{now - last};
        std::clog << msg << diff.count() << "ms\n";
        last = std::chrono::steady_clock::now();
    }
};

#endif// TIMER_HPP
