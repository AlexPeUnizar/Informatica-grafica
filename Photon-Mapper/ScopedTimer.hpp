#ifndef SCOPEDTIMER_HPP
#define SCOPEDTIMER_HPP

#include <iostream>
#include <chrono>

class ScopedTimer {
private:
    std::string timer_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
public:
    explicit ScopedTimer(const std::string& name);
    ~ScopedTimer();

};

#endif /* SCOPEDTIMER_HPP */