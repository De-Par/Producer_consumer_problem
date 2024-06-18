#pragma once

#include <string>
#include "utilities/UniqueIDGenerator.hpp"

static UniqueIDGenerator generator;

class Task {
private:
    std::string data_ = "Something task";
    std::string ID_ = generator.generateID();

public:
    ~Task() = default;

    std::string getID() {
        return ID_;
    }

    explicit operator std::string () const {
        return "task_" + ID_;
    }
};
