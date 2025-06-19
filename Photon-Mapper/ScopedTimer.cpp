#include "ScopedTimer.hpp"

ScopedTimer::ScopedTimer(const std::string& name) 
    : timer_name(name), start_time(std::chrono::high_resolution_clock::now()) {}
/*
ScopedTimer::~ScopedTimer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "[" << timer_name << "] Time: " << duration << " ms\n";
}
*/

ScopedTimer::~ScopedTimer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

    int hours = static_cast<int>(duration_sec / 3600);
    int minutes = static_cast<int>((duration_sec - hours * 3600) / 60);
    double seconds = duration_sec - hours * 3600 - minutes * 60;

    std::cout << "[" << timer_name << "] Time: ";
    if (hours > 0) std::cout << hours << "h ";
    if (minutes > 0 || hours > 0) std::cout << minutes << "m ";
    std::cout << seconds << "s" << std::endl;
}