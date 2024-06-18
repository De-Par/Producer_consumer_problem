#pragma once

#include <thread>
#include <iostream>
#include <chrono>
#include <atomic>
#include "BlockingQueue.hpp"
#include "utilities/SafeCout.hpp"

template<typename T>
class IProducer {
public:
    virtual ~IProducer() = default;
    virtual void produce() = 0;
};

template<typename T>
class Producer : public IProducer<T> {
private:
    BlockingQueue<T>& queue_;
    std::atomic<bool>& running_;
    size_t ID_;

public:
    ~Producer() = default;

    Producer(BlockingQueue<T>& queue, std::atomic<bool>& running, const size_t& ID) :
        queue_(queue), running_(running), ID_(ID) {}

    void produce() override {
        while (running_) {
            if (queue_.size() < queue_.capacity()) {
                const T item{};
                queue_.push(item);
                SafeCout() << "[" << queue_.size() << "/" << queue_.capacity() <<
                    "] Producer " << ID_ << " ---> " << static_cast<std::string>(item) << std::endl;
            } else {
                SafeCout() << "[" << queue_.size() << "/" << queue_.capacity() <<
                           "] Producer " << ID_ << " ---> none" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};