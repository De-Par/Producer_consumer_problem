#pragma once

#include <thread>
#include <iostream>
#include <atomic>
#include <vector>
#include "BlockingQueue.hpp"
#include "utilities/SafeCout.hpp"

template<typename T>
class IConsumer {
public:
    virtual ~IConsumer() = default;
    virtual void consume() = 0;
};

template<typename T>
class Consumer : public IConsumer<T> {
private:
    BlockingQueue<T>& queue_;
    std::atomic<bool>& running_;
    std::vector<T> consumed_products;
    size_t ID_;

public:
    ~Consumer() = default;

    Consumer(BlockingQueue<T>& queue, std::atomic<bool>& running, const size_t& ID) :
        queue_(queue), running_(running), ID_(ID) {}

    void consume() override {
        while (running_) {
            T item = queue_.pop();
            consumed_products.push_back(item);

            SafeCout() << "Consumer " << ID_ << " <--- " << static_cast<std::string>(item)
                << " [" << consumed_products.size() << "]" << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }

    std::vector<T>& getConsumedItems() {
        return consumed_products;
    }
};