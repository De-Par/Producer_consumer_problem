#pragma once

#include <iostream>
#include <mutex>

class SafeCout {
private:
    static std::mutex coutMutex;

public:
    template<typename T>
    SafeCout& operator<<(const T& data) {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << data;
        return *this;
    }

    // to handle std::endl and other manipulations...

    SafeCout& operator<<(std::ostream& (*manip)(std::ostream&)) {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << manip;
        return *this;
    }
};