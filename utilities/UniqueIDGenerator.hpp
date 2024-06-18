#pragma once

#include <iostream>
#include <chrono>
#include <atomic>
#include <sstream>
#include <iomanip>
#include <mutex>

class UniqueIDGenerator {
private:
    std::atomic<uint64_t> counter;
    std::mutex mtx;

public:
    UniqueIDGenerator() : counter(0) {}

    std::string generateID() {
        std::lock_guard<std::mutex> lock(mtx);

        // Get the current time as a high-resolution timestamp
        auto now = std::chrono::high_resolution_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        uint64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

        // Increment the counter
        uint64_t count = counter++;

        // Combine timestamp and counter to form a unique ID
        std::ostringstream oss;
        oss << timestamp << std::setw(6) << std::setfill('0') << count;

        return oss.str();
    }
};