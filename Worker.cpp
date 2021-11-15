#include <thread>
#include <iostream>
#include "Worker.h"

std::mutex Worker::mutex;

void Worker::notify() {
    {
        std::lock_guard<std::mutex> lock(mutex);
        sleeping = false;
    }
    condition.notify_one();
}

void Worker::stop() {
    {
        std::lock_guard<std::mutex> lock(mutex);
        running = false;
    }
    notify();
}

void Worker::process() {
    while (running) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [this]{return !sleeping;});
        }
        if (!running) {
            break;
        }
        std::cout << std::this_thread::get_id() << std::endl;
        sleeping = true;
    }
}