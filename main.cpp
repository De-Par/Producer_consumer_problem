#include <thread>
#include <atomic>
#include <list>

#include "BlockingQueue.hpp"
#include "Consumer.hpp"
#include "Producer.hpp"
#include "Task.hpp"
#include "utilities/SafeCout.hpp"

typedef Task Type;

const size_t num_producers = 2;
const size_t num_consumers = 5;
const size_t time_limit_sec = 120;
const size_t capacity = 100;

std::mutex SafeCout::coutMutex{};

int main() {
    BlockingQueue<Type> queue(capacity);
    std::atomic<bool> running(true);

    std::list<std::thread> producers;
    std::list<std::thread> consumers;

    for (size_t id = 0; id < num_producers; ++id) {
        Producer<Type> producer(queue, running, id);
        producers.emplace_back(&Producer<Type>::produce, producer);
    }

    for (size_t id = num_producers; id <= num_consumers; ++id) {
        Consumer<Type> consumer(queue, running, id);
        consumers.emplace_back(&Consumer<Type>::consume, consumer);
    }
    // Setup, how long do our threads run
    std::this_thread::sleep_for(std::chrono::seconds(time_limit_sec));

    running = false;

    for (auto &th : producers) th.join();
    for (auto &th : consumers) th.join();

    return 0;
}