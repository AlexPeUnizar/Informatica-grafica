#include "ScopedTimer.hpp"

ScopedTimer::ScopedTimer(const std::string& name) 
    : timer_name(name), start_time(std::chrono::high_resolution_clock::now()) {}

ScopedTimer::~ScopedTimer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "[" << timer_name << "] Time: " << duration << " ms\n";
}