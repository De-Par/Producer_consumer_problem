#include <thread>
#include <atomic>
#include <list>

#include "BlockingQueue.hpp"
#include "Consumer.hpp"
#include "Producer.hpp"
#include "Task.hpp"
#include "utilities/SafeCout.hpp"

typedef Task Type;

const size_t num_consumers = 5;
const size_t time_limit_sec = 120;
const size_t capacity = 100;

std::mutex SafeCout::coutMutex{};

int main() {
    BlockingQueue<Type> queue(capacity);
    std::atomic<bool> running(true);
    std::list<std::thread> consumers;

    Producer<Type> producer(queue, running, 0);
    std::thread producerThread(&Producer<Type>::produce, &producer);

    for (size_t id = 1; id <= num_consumers; ++id) {
        Consumer<Type> consumer(queue, running, id);
        consumers.emplace_back(&Consumer<Type>::consume, consumer);
    }
    // Setup, how long do our threads run
    std::this_thread::sleep_for(std::chrono::seconds(time_limit_sec));

    running = false;

    producerThread.join();
    for (auto &th : consumers) {
        th.join();
    }
    return 0;
}