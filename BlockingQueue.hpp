#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class IBlockingQueue {
public:
    virtual ~IBlockingQueue() = default;
    virtual void push(const T& item) = 0;
    virtual T pop() = 0;
};

template<typename T>
class BlockingQueue : public IBlockingQueue<T> {
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
    size_t capacity_;

public:
    ~BlockingQueue() = default;

    BlockingQueue() : capacity_(SIZE_T_MAX) {}

    explicit BlockingQueue(size_t capacity) : capacity_(capacity) {}

    void push(const T& item) override {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this]() { return queue_.size() < capacity_; });
        queue_.push(item);
        cond_.notify_one();
    }

    T pop() override {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this]() { return !queue_.empty(); });
        T item = queue_.front();
        queue_.pop();
        cond_.notify_one();
        return item;
    }

    size_t size() {
        return queue_.size();
    }

    size_t capacity() {
        return capacity_;
    }
};